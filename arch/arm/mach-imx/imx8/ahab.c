/*
 * Copyright 2018 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 */

#include <common.h>
#include <errno.h>
#include <asm/io.h>
#include <asm/mach-imx/sci/sci.h>
#include <asm/mach-imx/sys_proto.h>
#include <asm/arch-imx/cpu.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/cpu.h>
#include <asm/arch/image.h>

DECLARE_GLOBAL_DATA_PTR;

#define SEC_SECURE_RAM_BASE             (0x31800000UL)
#define SEC_SECURE_RAM_END_BASE         (SEC_SECURE_RAM_BASE + 0xFFFFUL)
#define SECO_LOCAL_SEC_SEC_SECURE_RAM_BASE  (0x60000000UL)

#define SECO_PT                 2U

int authenticate_os_container(ulong addr)
{
	struct container_hdr *phdr;
	int i, ret = 0;
	sc_ipc_t ipcHndl = gd->arch.ipc_channel_handle;
	sc_err_t err;
	sc_rm_mr_t mr;
	sc_faddr_t start, end;
	uint16_t length;

	if (addr % 4)
		return -EINVAL;

	phdr = (struct container_hdr *)addr;
	if (phdr->tag != 0x87 && phdr->version != 0x0) {
		printf("Wrong container header\n");
		return -EFAULT;
	}

	if (!phdr->num_images) {
		printf("Wrong container, no image found\n");
		return -EFAULT;
	}

	length = phdr->length_lsb + (phdr->length_msb << 8);

	debug("container length %u\n", length);
	memcpy((void *)SEC_SECURE_RAM_BASE, (const void *)addr, ALIGN(length, CONFIG_SYS_CACHELINE_SIZE));

	err = sc_seco_authenticate(ipcHndl, SC_MISC_AUTH_CONTAINER, SECO_LOCAL_SEC_SEC_SECURE_RAM_BASE);
	if (err) {
		printf("authenticate container hdr failed, return %d\n", err);
		ret = -EIO;
		goto exit;
	}

	/* Copy images to dest address */
	for (i=0; i < phdr->num_images; i++) {
		struct boot_img_t *img = (struct boot_img_t *)(addr + sizeof(struct container_hdr) + i * sizeof(struct boot_img_t));

		debug("img %d, dst 0x%llx, src 0x%lx, size 0x%x\n", i, img->dst, img->offset + addr, img->size);

		memcpy((void *)img->dst, (const void *)(img->offset + addr), img->size);
		flush_dcache_range(img->dst & ~(CONFIG_SYS_CACHELINE_SIZE - 1),
				ALIGN(img->dst + img->size, CONFIG_SYS_CACHELINE_SIZE));

		/* Find the memreg and set permission for seco pt */
		err = sc_rm_find_memreg(ipcHndl, &mr,
			img->dst & ~(CONFIG_SYS_CACHELINE_SIZE - 1), ALIGN(img->dst + img->size, CONFIG_SYS_CACHELINE_SIZE));

		if (err) {
			printf("can't find memreg for image load address %d, error %d\n", i, err);
			ret = -ENOMEM;
			goto exit;
		}

		err = sc_rm_get_memreg_info(ipcHndl, mr, &start, &end);
		if (!err)
			debug("memreg %u 0x%llx -- 0x%llx\n", mr, start, end);

		err = sc_rm_set_memreg_permissions(ipcHndl, mr, SECO_PT, SC_RM_PERM_FULL);
		if (err) {
			printf("set permission failed for img %d, error %d\n", i, err);
			ret = -EPERM;
			goto exit;
		}

		err = sc_seco_authenticate(ipcHndl, SC_MISC_VERIFY_IMAGE, (1 << i));
		if (err) {
			printf("authenticate img %d failed, return %d\n", i, err);
			ret = -EIO;
		}

		err = sc_rm_set_memreg_permissions(ipcHndl, mr, SECO_PT, SC_RM_PERM_NONE);
		if (err) {
			printf("remove permission failed for img %d, error %d\n", i, err);
			ret = -EPERM;
		}

		if (ret)
			goto exit;
	}

exit:
	sc_seco_authenticate(ipcHndl, SC_MISC_REL_CONTAINER, 0);

	return ret;
}


static int do_authenticate(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong addr;
	if (argc < 2)
		return CMD_RET_USAGE;

	addr = simple_strtoul(argv[1], NULL, 16);

	printf("Authenticate OS container at 0x%lx \n", addr);

	if (authenticate_os_container(addr))
		return CMD_RET_FAILURE;

	return CMD_RET_SUCCESS;
}

static void display_life_cycle(uint16_t lc)
{
	printf("Lifecycle: 0x%04X, ", lc);
	switch (lc) {
	case 0x1:
		printf("Pristine\n\n");
		break;
	case 0x2:
		printf("Fab\n\n");
		break;
	case 0x8:
		printf("Open\n\n");
		break;
	case 0x20:
		printf("NXP closed\n\n");
		break;
	case 0x80:
		printf("OEM closed\n\n");
		break;
	case 0x100:
		printf("Partial field return\n\n");
		break;
	case 0x200:
		printf("Full field return\n\n");
		break;
	case 0x400:
		printf("No return\n\n");
		break;
	default:
		printf("Unknown\n\n");
		break;
	}
}

#define AHAB_AUTH_CONTAINER_REQ 0x87

#define AHAB_NO_AUTHENTICATION_IND 0xee
#define AHAB_BAD_KEY_HASH_IND 0xfa
#define AHAB_INVALID_KEY_IND 0xf9
#define AHAB_BAD_SIGNATURE_IND 0xf0
#define AHAB_BAD_HASH_IND 0xf1

static void display_ahab_auth_event(uint32_t event)
{
	uint8_t cmd = (event >> 16) & 0xff;
	uint8_t resp_ind =(event >> 8) & 0xff;

	if (cmd != AHAB_AUTH_CONTAINER_REQ)
		return;

	printf("\tCMD = AHAB_AUTH_CONTAINER_REQ (0x%02X)\n", cmd);
	printf("\tIND = ");
	switch (resp_ind) {
	case AHAB_NO_AUTHENTICATION_IND:
		printf("AHAB_NO_AUTHENTICATION_IND (0x%02X)\n\n", resp_ind);
		break;
	case AHAB_BAD_KEY_HASH_IND:
		printf("AHAB_BAD_KEY_HASH_IND (0x%02X)\n\n", resp_ind);
		break;
	case AHAB_INVALID_KEY_IND:
		printf("AHAB_INVALID_KEY_IND (0x%02X)\n\n", resp_ind);
		break;
	case AHAB_BAD_SIGNATURE_IND:
		printf("AHAB_BAD_SIGNATURE_IND (0x%02X)\n\n", resp_ind);
		break;
	case AHAB_BAD_HASH_IND:
		printf("AHAB_BAD_HASH_IND (0x%02X)\n\n", resp_ind);
		break;
	default:
		printf("Unknown Indicator (0x%02X)\n\n", resp_ind);
		break;
	}
}


static int do_ahab_status(cmd_tbl_t *cmdtp, int flag, int argc,
			 char * const argv[])
{
	sc_err_t err;
	uint8_t idx = 0U;
	uint32_t event;
	uint16_t lc;
	sc_ipc_t ipcHndl = gd->arch.ipc_channel_handle;

	err = sc_seco_chip_info(ipcHndl, &lc, NULL, NULL, NULL);
	if (err != SC_ERR_NONE) {
		printf("Error in get lifecycle\n");
		return -EIO;
	}

	display_life_cycle(lc);

	err = sc_seco_get_event(ipcHndl, idx, &event);
	while (err == SC_ERR_NONE) {
		printf ("SECO Event[%u] = 0x%08X\n", idx, event);
		display_ahab_auth_event(event);

		idx++;
		err = sc_seco_get_event(ipcHndl, idx, &event);
	}

	if (idx == 0)
		printf("No SECO Events Found!\n\n");

	return 0;
}

U_BOOT_CMD(
	auth_cntr, CONFIG_SYS_MAXARGS, 1, do_authenticate,
	"autenticate OS container via AHAB",
	"addr\n"
	"addr - OS container hex address\n"
);

U_BOOT_CMD(
	ahab_status, CONFIG_SYS_MAXARGS, 1, do_ahab_status,
	"display AHAB lifecycle and events from seco",
	""
  );
