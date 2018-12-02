/*
 * Copyright 2017 NXP
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 */

#include <common.h>
#include <errno.h>
#include <asm/io.h>
#include <power-domain.h>
#include <dm/device.h>
#include <dm/uclass-internal.h>
#include <asm/imx-common/sci/sci.h>
#include <asm/imx-common/boot_mode.h>
#include <asm/arch/clock.h>
#include <asm/armv8/mmu.h>
#include <elf.h>
#include <asm/arch/sid.h>
#include <asm/arch-imx/cpu.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/video_common.h>
#include <libfdt.h>
#include <fdt_support.h>
#include <fdtdec.h>
#include <thermal.h>
#include <asm/arch/cpu.h>

DECLARE_GLOBAL_DATA_PTR;

u32 get_cpu_rev(void)
{
	sc_ipc_t ipcHndl;
	uint32_t id = 0, rev = 0;
	sc_err_t err;

	ipcHndl = gd->arch.ipc_channel_handle;

	err = sc_misc_get_control(ipcHndl, SC_R_SC_PID0, SC_C_ID, &id);
	if (err != SC_ERR_NONE)
		return 0;

	rev = (id >> 5)  & 0xf;
	id = (id & 0x1f) + MXC_SOC_IMX8;  /* Dummy ID for chip */

	return (id << 12) | rev;
}

#ifdef CONFIG_DISPLAY_CPUINFO
const char *get_imx8_type(u32 imxtype)
{
	switch (imxtype) {
	case MXC_CPU_IMX8QM:
		return "8QM";	/* i.MX8 Quad MAX */
	case MXC_CPU_IMX8QXP:
		return "8QXP";	/* i.MX8 Quad XP */
	case MXC_CPU_IMX8DX:
		return "8DX";	/* i.MX8 Dual X */
	default:
		return "??";
	}
}

const char *get_imx8_rev(u32 rev)
{
	switch (rev) {
	case CHIP_REV_A:
		return "A";
	case CHIP_REV_B:
		return "B";
	default:
		return "?";
	}
}

const char *get_core_name(void)
{
	if (is_cortex_a53())
		return "A53";
	else if (is_cortex_a35())
		return "A35";
	else if (is_cortex_a72())
		return "A72";
	else
		return "?";
}


int print_cpuinfo(void)
{
	u32 cpurev;

	cpurev = get_cpu_rev();

	printf("CPU:   Freescale i.MX%s rev%s %s at %d MHz",
			get_imx8_type((cpurev & 0xFF000) >> 12),
			get_imx8_rev((cpurev & 0xFFF)),
			get_core_name(),
		mxc_get_clock(MXC_ARM_CLK) / 1000000);

#if defined(CONFIG_IMX_SC_THERMAL)
	struct udevice *thermal_dev;
	int cpu_tmp, ret;

	if (is_imx8qm() && is_cortex_a72())
		ret = uclass_get_device_by_name(UCLASS_THERMAL, "cpu-thermal1", &thermal_dev);
	else
		ret = uclass_get_device_by_name(UCLASS_THERMAL, "cpu-thermal0", &thermal_dev);

	if (!ret) {
		ret = thermal_get_temp(thermal_dev, &cpu_tmp);

		if (!ret)
			printf(" at %dC", cpu_tmp);
		else
			debug(" - invalid sensor data");
	} else {
		debug(" - invalid sensor device");
	}
#endif

	printf("\n");
	return 0;
}
#endif

#define BT_PASSOVER_TAG             (0x504F)
struct pass_over_info_t *get_pass_over_info(void)
{
	struct pass_over_info_t *p = (struct pass_over_info_t *)PASS_OVER_INFO_ADDR;

	if (p->barker != BT_PASSOVER_TAG || p->len != sizeof(struct pass_over_info_t))
		return NULL;

	return p;
}

int arch_cpu_init(void)
{
	sc_ipc_t ipcHndl = 0;
	sc_err_t sciErr = 0;
	struct pass_over_info_t *pass_over;

	gd->arch.ipc_channel_handle = 0;

	/* Open IPC channel */
	sciErr = sc_ipc_open(&ipcHndl, SC_IPC_CH);
	if (sciErr != SC_ERR_NONE)
		return -EPERM;

	gd->arch.ipc_channel_handle = ipcHndl;

	pass_over = get_pass_over_info();
	if (pass_over && pass_over->g_ap_mu == 0) {
		/* When ap_mu is 0, means the u-boot is boot from first container */
		sc_misc_boot_status(ipcHndl, SC_MISC_BOOT_STATUS_SUCCESS);
	}

#ifdef CONFIG_IMX_SMMU
	sciErr = sc_pm_set_resource_power_mode(ipcHndl, SC_R_SMMU,
				SC_PM_PW_MODE_ON);
	if (sciErr != SC_ERR_NONE)
		return 0;
#endif

	return 0;
}

u32 cpu_mask(void)
{
#ifdef CONFIG_IMX8QM
	return 0x3f;
#else
	return 0xf;	/*For IMX8QXP*/
#endif
}

#define CCI400_DVM_MESSAGE_REQ_EN	0x00000002
#define CCI400_SNOOP_REQ_EN		0x00000001
#define CHANGE_PENDING_BIT		(1 << 0)
int imx8qm_wake_seconday_cores(void)
{
#ifdef CONFIG_ARMV8_MULTIENTRY
	sc_ipc_t ipcHndl;
	u64 *table = get_spin_tbl_addr();

	/* Clear spin table so that secondary processors
	 * observe the correct value after waking up from wfe.
	 */
	memset(table, 0, CONFIG_MAX_CPUS*SPIN_TABLE_ELEM_SIZE);
	flush_dcache_range((unsigned long)table,
			   (unsigned long)table +
			   (CONFIG_MAX_CPUS*SPIN_TABLE_ELEM_SIZE));

	/* Open IPC channel */
	if (sc_ipc_open(&ipcHndl, SC_IPC_CH)  != SC_ERR_NONE)
		return -EIO;

	__raw_writel(0xc, 0x52090000);
	__raw_writel(1, 0x52090008);

	/* IPC to pwr up and boot other cores */
	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A53_1, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;
	if (sc_pm_cpu_start(ipcHndl, SC_R_A53_1, true, 0x80000000) != SC_ERR_NONE)
		return -EIO;

	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A53_2, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;
	if (sc_pm_cpu_start(ipcHndl, SC_R_A53_2, true, 0x80000000) != SC_ERR_NONE)
		return -EIO;

	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A53_3, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;
	if (sc_pm_cpu_start(ipcHndl, SC_R_A53_3, true, 0x80000000) != SC_ERR_NONE)
		return -EIO;

	/* Enable snoop and dvm msg requests for a53 port on CCI slave interface 3 */
	__raw_writel(CCI400_DVM_MESSAGE_REQ_EN | CCI400_SNOOP_REQ_EN, 0x52094000);

	while (__raw_readl(0x5209000c) & CHANGE_PENDING_BIT)
		;

	/* Pwr up cluster 1 and boot core 0*/
	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A72, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;

	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A72_0, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;
	if (sc_pm_cpu_start(ipcHndl, SC_R_A72_0, true, 0x80000000) != SC_ERR_NONE)
		return -EIO;

	/* IPC to pwr up and boot core 1 */
	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A72_1, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;
	if (sc_pm_cpu_start(ipcHndl, SC_R_A72_1, true, 0x80000000) != SC_ERR_NONE)
		return -EIO;

	/* Enable snoop and dvm msg requests for a72 port on CCI slave interface 4 */
	__raw_writel(CCI400_DVM_MESSAGE_REQ_EN | CCI400_SNOOP_REQ_EN, 0x52095000);

	while (__raw_readl(0x5209000c) & CHANGE_PENDING_BIT)
		;
#endif
	return 0;
}

int imx8qxp_wake_secondary_cores(void)
{
#ifdef CONFIG_ARMV8_MULTIENTRY
	sc_ipc_t ipcHndl;
	u64 *table = get_spin_tbl_addr();

	/* Clear spin table so that secondary processors
	 * observe the correct value after waking up from wfe.
	 */
	memset(table, 0, CONFIG_MAX_CPUS*SPIN_TABLE_ELEM_SIZE);
	flush_dcache_range((unsigned long)table,
			   (unsigned long)table +
			   (CONFIG_MAX_CPUS*SPIN_TABLE_ELEM_SIZE));

	/* Open IPC channel */
	if (sc_ipc_open(&ipcHndl, SC_IPC_CH)  != SC_ERR_NONE)
		return -EIO;

	/* IPC to pwr up and boot other cores */
	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A35_1, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;
	if (sc_pm_cpu_start(ipcHndl, SC_R_A35_1, true, 0x80000000) != SC_ERR_NONE)
		return -EIO;

	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A35_2, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;
	if (sc_pm_cpu_start(ipcHndl, SC_R_A35_2, true, 0x80000000) != SC_ERR_NONE)
		return -EIO;

	if (sc_pm_set_resource_power_mode(ipcHndl, SC_R_A35_3, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;
	if (sc_pm_cpu_start(ipcHndl, SC_R_A35_3, true, 0x80000000) != SC_ERR_NONE)
		return -EIO;

#endif
	return 0;
}

#define FUSE_MAC0_WORD0 452
#define FUSE_MAC0_WORD1 453
#define FUSE_MAC1_WORD0 454
#define FUSE_MAC1_WORD1 455
void imx_get_mac_from_fuse(int dev_id, unsigned char *mac)
{
	sc_err_t err;
	sc_ipc_t ipc;
	uint32_t val1 = 0, val2 = 0;
	uint32_t word1, word2;

	ipc = gd->arch.ipc_channel_handle;

	if (dev_id == 0) {
		word1 = FUSE_MAC0_WORD0;
		word2 = FUSE_MAC0_WORD1;
	} else {
		word1 = FUSE_MAC1_WORD0;
		word2 = FUSE_MAC1_WORD1;
	}

	err = sc_misc_otp_fuse_read(ipc, word1, &val1);
	if (err != SC_ERR_NONE) {
		printf("%s fuse %d read error: %d\n", __func__, word1, err);
		return;
	}

	err = sc_misc_otp_fuse_read(ipc, word2, &val2);
	if (err != SC_ERR_NONE) {
		printf("%s fuse %d read error: %d\n", __func__, word2, err);
		return;
	}

	mac[0] = val1;
	mac[1] = val1 >> 8;
	mac[2] = val1 >> 16;
	mac[3] = val1 >> 24;
	mac[4] = val2;
	mac[5] = val2 >> 8;
}

#ifdef CONFIG_IMX_BOOTAUX

#ifdef CONFIG_IMX8QM
int arch_auxiliary_core_up(u32 core_id, ulong boot_private_data)
{
	sc_ipc_t ipcHndl;
	sc_rsrc_t core_rsrc, mu_rsrc;
	sc_faddr_t tcml_addr;
	u32 tcml_size = SZ_128K;
	ulong addr;

	ipcHndl = gd->arch.ipc_channel_handle;

	switch (core_id) {
	case 0:
		core_rsrc = SC_R_M4_0_PID0;
		tcml_addr = 0x34FE0000;
		mu_rsrc = SC_R_M4_0_MU_1A;
		break;
	case 1:
		core_rsrc = SC_R_M4_1_PID0;
		tcml_addr = 0x38FE0000;
		mu_rsrc = SC_R_M4_1_MU_1A;
		break;
	default:
		printf("Not support this core boot up, ID:%u\n", core_id);
		return -EINVAL;
	}

	addr = (sc_faddr_t)boot_private_data;

	if (addr >= tcml_addr && addr <= tcml_addr + tcml_size) {
		printf("Wrong image address 0x%lx, should not in TCML\n",
			addr);
		return -EINVAL;
	}

	printf("Power on M4 and MU\n");

	if (sc_pm_set_resource_power_mode(ipcHndl, core_rsrc, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;

	if (sc_pm_set_resource_power_mode(ipcHndl, mu_rsrc, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;

	printf("Copy M4 image from 0x%lx to TCML 0x%lx\n", addr, (ulong)tcml_addr);

	if (addr != tcml_addr)
		memcpy((void *)tcml_addr, (void *)addr, tcml_size);

	printf("Start M4 %u\n", core_id);
	if (sc_pm_cpu_start(ipcHndl, core_rsrc, true, tcml_addr) != SC_ERR_NONE)
		return -EIO;

	printf("bootaux complete\n");
	return 0;
}
#endif

#ifdef CONFIG_IMX8QXP
static unsigned long load_elf_image_shdr(unsigned long addr)
{
	Elf32_Ehdr *ehdr; /* Elf header structure pointer */
	Elf32_Shdr *shdr; /* Section header structure pointer */
	unsigned char *strtab = 0; /* String table pointer */
	unsigned char *image; /* Binary image pointer */
	int i; /* Loop counter */

	ehdr = (Elf32_Ehdr *)addr;

	/* Find the section header string table for output info */
	shdr = (Elf32_Shdr *)(addr + ehdr->e_shoff +
			     (ehdr->e_shstrndx * sizeof(Elf32_Shdr)));

	if (shdr->sh_type == SHT_STRTAB)
		strtab = (unsigned char *)(addr + shdr->sh_offset);

	/* Load each appropriate section */
	for (i = 0; i < ehdr->e_shnum; ++i) {
		shdr = (Elf32_Shdr *)(addr + ehdr->e_shoff +
				     (i * sizeof(Elf32_Shdr)));

		if (!(shdr->sh_flags & SHF_ALLOC) ||
		    shdr->sh_addr == 0 || shdr->sh_size == 0) {
			continue;
		}

		if (strtab) {
			debug("%sing %s @ 0x%08lx (%ld bytes)\n",
			      (shdr->sh_type == SHT_NOBITS) ? "Clear" : "Load",
			       &strtab[shdr->sh_name],
			       (unsigned long)shdr->sh_addr,
			       (long)shdr->sh_size);
		}

		if (shdr->sh_type == SHT_NOBITS) {
			memset((void *)(uintptr_t)shdr->sh_addr, 0,
			       shdr->sh_size);
		} else {
			image = (unsigned char *)addr + shdr->sh_offset;
			memcpy((void *)(uintptr_t)shdr->sh_addr,
			       (const void *)image, shdr->sh_size);
		}
		flush_cache(shdr->sh_addr, shdr->sh_size);
	}

	return ehdr->e_entry;
}

int arch_auxiliary_core_up(u32 core_id, ulong boot_private_data)
{
	sc_ipc_t ipcHndl;
	sc_rsrc_t core_rsrc, mu_rsrc = -1;
	sc_faddr_t aux_core_ram;
	u32 size;
	ulong addr;

	ipcHndl = gd->arch.ipc_channel_handle;

	switch (core_id) {
	case 0:
		core_rsrc = SC_R_M4_0_PID0;
		aux_core_ram = 0x34FE0000;
		mu_rsrc = SC_R_M4_0_MU_1A;
		size = SZ_128K;
		break;
	case 1:
		core_rsrc = SC_R_HIFI;
		aux_core_ram = 0x596f8000;
		size = SZ_2K;
		break;
	default:
		printf("Not support this core boot up, ID:%u\n", core_id);
		return -EINVAL;
	}

	addr = (sc_faddr_t)boot_private_data;

	if (addr >= aux_core_ram && addr <= aux_core_ram + size) {
		printf("Wrong image address 0x%lx, should not in aux core ram\n",
			addr);
		return -EINVAL;
	}

	printf("Power on aux core %d\n", core_id);

	if (sc_pm_set_resource_power_mode(ipcHndl, core_rsrc, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
		return -EIO;

	if (mu_rsrc != -1) {
		if (sc_pm_set_resource_power_mode(ipcHndl, mu_rsrc, SC_PM_PW_MODE_ON) != SC_ERR_NONE)
			return -EIO;
	}

	if (core_id == 1) {
		struct power_domain pd;

		if (sc_pm_clock_enable(ipcHndl, core_rsrc, SC_PM_CLK_PER, true, false) != SC_ERR_NONE) {
			printf("Error enable clock\n");
			return -EIO;
		}

		if (!power_domain_lookup_name("audio_sai0", &pd)) {
			if (power_domain_on(&pd)) {
				printf("Error power on SAI0\n");
				return -EIO;
			}
		}

		if (!power_domain_lookup_name("audio_ocram", &pd)) {
			if (power_domain_on(&pd)) {
				printf("Error power on HIFI RAM\n");
				return -EIO;
			}
		}
	}

	printf("Copy image from 0x%lx to 0x%lx\n", addr, (ulong)aux_core_ram);
	if (core_id == 0) {
		/* M4 use bin file */
		memcpy((void *)aux_core_ram, (void *)addr, size);
	} else {
		/* HIFI use elf file */
		if (!valid_elf_image(addr))
			return -1;
		addr = load_elf_image_shdr(addr);
	}

	printf("Start %s\n", core_id == 0 ? "M4" : "HIFI");

	if (sc_pm_cpu_start(ipcHndl, core_rsrc, true, aux_core_ram) != SC_ERR_NONE)
		return -EIO;

	printf("bootaux complete\n");
	return 0;
}
#endif

int arch_auxiliary_core_check_up(u32 core_id)
{
	sc_rsrc_t core_rsrc;
	sc_pm_power_mode_t power_mode;
	sc_ipc_t ipcHndl;

	ipcHndl = gd->arch.ipc_channel_handle;

	switch (core_id) {
	case 0:
		core_rsrc = SC_R_M4_0_PID0;
		break;
#ifdef CONFIG_IMX8QM
	case 1:
		core_rsrc = SC_R_M4_1_PID0;
		break;
#endif
	default:
		printf("Not support this core, ID:%u\n", core_id);
		return 0;
	}

	if (sc_pm_get_resource_power_mode(ipcHndl, core_rsrc, &power_mode) != SC_ERR_NONE)
		return 0;

	if (power_mode != SC_PM_PW_MODE_OFF)
		return 1;

	return 0;
}
#endif

#ifdef CONFIG_IMX_SMMU
struct smmu_sid dev_sids[] = {
	{ SC_R_SDHC_0, 0x11, "SDHC0" },
	{ SC_R_SDHC_1, 0x11, "SDHC1" },
	{ SC_R_SDHC_2, 0x11, "SDHC2" },
	{ SC_R_ENET_0, 0x12, "FEC0" },
	{ SC_R_ENET_1, 0x12, "FEC1" },
};

sc_err_t imx8_config_smmu_sid(struct smmu_sid *dev_sids, int size)
{
	int i;
	sc_err_t sciErr = SC_ERR_NONE;

	if ((dev_sids == NULL) || (size <= 0))
		return SC_ERR_NONE;

	for (i = 0; i < size; i++) {
		sciErr = sc_rm_set_master_sid(gd->arch.ipc_channel_handle,
					      dev_sids[i].rsrc,
					      dev_sids[i].sid);
		if (sciErr != SC_ERR_NONE) {
			printf("set master sid error\n");
			return sciErr;
		}
	}

	return SC_ERR_NONE;
}
#endif

void arch_preboot_os(void)
{
#if defined(CONFIG_VIDEO_IMXDPUV1)
	imxdpuv1_fb_disable();
#endif
#ifdef CONFIG_IMX_SMMU
	imx8_config_smmu_sid(dev_sids, ARRAY_SIZE(dev_sids));
#endif
}


enum boot_device get_boot_device(void)
{
	struct rom_sw_info_t **p =
		(struct rom_sw_info_t **)ROM_SW_INFO_ADDR;

	enum boot_device boot_dev = SD1_BOOT;
	uint8_t boot_type = (*p)->boot_dev_info.dev_type;
	uint8_t boot_instance = (*p)->boot_dev_info.instance;

	switch (boot_type) {
	case FLASH_TYPE_SD:
		boot_dev = boot_instance + SD1_BOOT;
		break;
	case FLASH_TYPE_MMC:
		boot_dev = boot_instance + MMC1_BOOT;
		break;
	case FLASH_TYPE_NAND:
		boot_dev = NAND_BOOT;
		break;
	case FLASH_TYPE_FLEXSPINOR:
		boot_dev = QSPI_BOOT;
		break;
	case BT_DEV_TYPE_SATA_DISK:
		boot_dev = SATA_BOOT;
		break;
	case BT_DEV_TYPE_USB:
		boot_dev = USB_BOOT;
		break;
	default:
		break;
	}

	return boot_dev;
}

bool is_usb_boot(void)
{
	return get_boot_device() == USB_BOOT;
}

int print_bootinfo(void)
{
	enum boot_device bt_dev;
	bt_dev = get_boot_device();

	puts("Boot:  ");
	switch (bt_dev) {
	case SD1_BOOT:
		puts("SD0\n");
		break;
	case SD2_BOOT:
		puts("SD1\n");
		break;
	case SD3_BOOT:
		puts("SD2\n");
		break;
	case MMC1_BOOT:
		puts("MMC0\n");
		break;
	case MMC2_BOOT:
		puts("MMC1\n");
		break;
	case MMC3_BOOT:
		puts("MMC2\n");
		break;
	case FLEXSPI_BOOT:
		puts("FLEXSPI\n");
		break;
	case SATA_BOOT:
		puts("SATA\n");
		break;
	case NAND_BOOT:
		puts("NAND\n");
		break;
	case USB_BOOT:
		puts("USB\n");
		break;
	default:
		printf("Unknown device %u\n", bt_dev);
		break;
	}

	return 0;
}

#ifdef CONFIG_SERIAL_TAG
#define FUSE_UNIQUE_ID_WORD0 16
#define FUSE_UNIQUE_ID_WORD1 17
void get_board_serial(struct tag_serialnr *serialnr)
{
	sc_err_t err;
	sc_ipc_t ipc;
	uint32_t val1 = 0, val2 = 0;
	uint32_t word1, word2;

	ipc = gd->arch.ipc_channel_handle;

	word1 = FUSE_UNIQUE_ID_WORD0;
	word2 = FUSE_UNIQUE_ID_WORD1;

	err = sc_misc_otp_fuse_read(ipc, word1, &val1);
	if (err != SC_ERR_NONE) {
		printf("%s fuse %d read error: %d\n", __func__,word1, err);
		return;
	}

	err = sc_misc_otp_fuse_read(ipc, word2, &val2);
	if (err != SC_ERR_NONE) {
		printf("%s fuse %d read error: %d\n", __func__, word2, err);
		return;
	}
	serialnr->low = val1;
	serialnr->high = val2;
}
#endif /*CONFIG_SERIAL_TAG*/

#ifdef CONFIG_ENV_IS_IN_MMC
__weak int board_mmc_get_env_dev(int devno)
{
	return CONFIG_SYS_MMC_ENV_DEV;
}

int mmc_get_env_dev(void)
{
	struct rom_sw_info_t **p = (struct rom_sw_info_t **)ROM_SW_INFO_ADDR;

	int devno = (*p)->boot_dev_info.instance;
	uint8_t boot_type = (*p)->boot_dev_info.dev_type;

	/* If not boot from sd/mmc, use default value */
	if ((boot_type != FLASH_TYPE_SD) && (boot_type != FLASH_TYPE_MMC))
		return CONFIG_SYS_MMC_ENV_DEV;

	return board_mmc_get_env_dev(devno);
}
#endif

static bool check_owned_resource(sc_rsrc_t rsrc_id)
{
	sc_ipc_t ipcHndl = 0;
	bool owned;

	ipcHndl = gd->arch.ipc_channel_handle;

	owned = sc_rm_is_resource_owned(ipcHndl, rsrc_id);

	return owned;
}

static int disable_fdt_node(void *blob, int nodeoffset)
{
	int rc, ret;
	const char *status = "disabled";

	do {
		rc = fdt_setprop(blob, nodeoffset, "status", status, strlen(status) + 1);
		if (rc) {
			if (rc == -FDT_ERR_NOSPACE) {
				ret = fdt_increase_size(blob, 512);
				if (ret)
					return ret;
			}
		}
	} while (rc == -FDT_ERR_NOSPACE);

	return rc;
}

static void update_fdt_with_owned_resources(void *blob)
{
	/* Traverses the fdt nodes,
	  * check its power domain and use the resource id in the power domain
	  * for checking whether it is owned by current partition
	  */

	int offset = 0, next_off, addr;
	int depth, next_depth;
	unsigned int rsrc_id;
	const fdt32_t *php;
	int rc;

	for (offset = fdt_next_node(blob, offset, &depth); offset > 0;
		 offset = fdt_next_node(blob, offset, &depth)) {

		debug("Node name: %s, depth %d\n", fdt_get_name(blob, offset, NULL), depth);

		if (!fdtdec_get_is_enabled(blob, offset)) {
			debug("   - ignoring disabled device\n");
			continue;
		}

		if (!fdt_node_check_compatible(blob, offset, "nxp,imx8-pd")) {
			/* Skip to next depth=1 node*/
			next_off = offset;
			next_depth = depth;
			do {
				offset = next_off;
				depth = next_depth;
				next_off = fdt_next_node(blob, offset, &next_depth);
				if (next_off < 0 || next_depth < 1)
					break;

				debug("PD name: %s, offset %d, depth %d\n",
					fdt_get_name(blob, next_off, NULL), next_off, next_depth);
			} while (next_depth > 1);

			continue;
		}

		php = fdt_getprop(blob, offset, "power-domains", NULL);
		if (!php) {
			debug("   - ignoring no power-domains\n");
		} else {
			addr = fdt_node_offset_by_phandle(blob, fdt32_to_cpu(*php));
			rsrc_id = fdtdec_get_uint(blob, addr, "reg", 0);

			debug("power-domains phandle 0x%x, addr 0x%x, resource id %u\n",
				fdt32_to_cpu(*php), addr, rsrc_id);

			if (!check_owned_resource(rsrc_id)) {

				/* If the resource is not owned, disable it in FDT */
				rc = disable_fdt_node(blob, offset);
				if (!rc)
					printf("Disable %s, resource id %u, pd phandle 0x%x\n",
						fdt_get_name(blob, offset, NULL), rsrc_id, fdt32_to_cpu(*php));
				else
					printf("Unable to disable %s, err=%s\n",
						fdt_get_name(blob, offset, NULL), fdt_strerror(rc));
			}
		}
	}
}

#ifdef CONFIG_OF_SYSTEM_SETUP
int ft_system_setup(void *blob, bd_t *bd)
{
#ifdef BOOTAUX_RESERVED_MEM_BASE
	int off;
	off = fdt_add_mem_rsv(blob, BOOTAUX_RESERVED_MEM_BASE,
				      BOOTAUX_RESERVED_MEM_SIZE);
		if (off < 0)
			printf("Failed  to reserve memory for bootaux: %s\n",
			       fdt_strerror(off));
#endif

	update_fdt_with_owned_resources(blob);

	return 0;
}
#endif

#define MEMSTART_ALIGNMENT  SZ_2M /* Align the memory start with 2MB */

static int get_owned_memreg(sc_rm_mr_t mr, sc_faddr_t *addr_start, sc_faddr_t *addr_end)
{
	sc_ipc_t ipcHndl = 0;
	sc_err_t sciErr = 0;
	bool owned;
	sc_faddr_t start, end;

	ipcHndl = gd->arch.ipc_channel_handle;

	if (ipcHndl) {
		owned = sc_rm_is_memreg_owned(ipcHndl, mr);
		if (owned) {
			sciErr = sc_rm_get_memreg_info(ipcHndl, mr, &start, &end);
			if (sciErr) {
				printf("Memreg get info failed, %d\n", sciErr);
				return -EINVAL;
			} else {
				debug("0x%llx -- 0x%llx\n", start, end);

				*addr_start = start;
				*addr_end = end;

				return 0;
			}
		}
	}

	return -EINVAL;
}

phys_size_t get_effective_memsize(void)
{
	sc_rm_mr_t mr;
	sc_faddr_t start, end;
	int err;

	for (mr = 0; mr < 64; mr++) {
		err = get_owned_memreg(mr, &start, &end);
		if (!err) {
			start = roundup(start, MEMSTART_ALIGNMENT);
			if (start > end) /* Too small memory region, not use it */
				continue;

			/* Find the memory region runs the u-boot */
			if (start >= PHYS_SDRAM_1 && start <= ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)
				&& (start <= CONFIG_SYS_TEXT_BASE && CONFIG_SYS_TEXT_BASE <= end)){
				if ((end + 1) <= ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))
					return (end - start + 1);
				else
					return PHYS_SDRAM_1_SIZE;
			}
		}
	}

	return PHYS_SDRAM_1_SIZE;
}

int dram_init(void)
{
	sc_rm_mr_t mr;
	sc_faddr_t start, end;
	int err;

	for (mr = 0; mr < 64; mr++) {
		err = get_owned_memreg(mr, &start, &end);
		if (!err) {
			start = roundup(start, MEMSTART_ALIGNMENT);
			if (start > end) /* Too small memory region, not use it */
				continue;

			if (start >= PHYS_SDRAM_1 && start <= ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)) {

				if ((end + 1) <= ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))
					gd->ram_size += end - start + 1;
				else
					gd->ram_size += PHYS_SDRAM_1_SIZE;

			} else if (start >= PHYS_SDRAM_2 && start <= ((sc_faddr_t)PHYS_SDRAM_2 + PHYS_SDRAM_2_SIZE)) {

				if ((end + 1) <= ((sc_faddr_t)PHYS_SDRAM_2 + PHYS_SDRAM_2_SIZE))
					gd->ram_size += end - start + 1;
				else
					gd->ram_size += PHYS_SDRAM_2_SIZE;
			}
		}
	}

	/* If error, set to the default value */
	if (!gd->ram_size) {
		gd->ram_size = PHYS_SDRAM_1_SIZE;
		gd->ram_size += PHYS_SDRAM_2_SIZE;
	}
	return 0;
}

static void dram_bank_sort(int current_bank)
{
	phys_addr_t start;
	phys_size_t size;
	while (current_bank > 0) {
		if (gd->bd->bi_dram[current_bank - 1].start > gd->bd->bi_dram[current_bank].start) {
			start = gd->bd->bi_dram[current_bank - 1].start;
			size = gd->bd->bi_dram[current_bank - 1].size;

			gd->bd->bi_dram[current_bank - 1].start = gd->bd->bi_dram[current_bank].start;
			gd->bd->bi_dram[current_bank - 1].size = gd->bd->bi_dram[current_bank].size;

			gd->bd->bi_dram[current_bank].start = start;
			gd->bd->bi_dram[current_bank].size = size;
		}

		current_bank--;
	}
}

void dram_init_banksize(void)
{
	sc_rm_mr_t mr;
	sc_faddr_t start, end;
	int i = 0;
	int err;

	for (mr = 0; mr < 64 && i < CONFIG_NR_DRAM_BANKS; mr++) {
		err = get_owned_memreg(mr, &start, &end);
		if (!err) {
			start = roundup(start, MEMSTART_ALIGNMENT);
			if (start > end) /* Too small memory region, not use it */
				continue;

			if (start >= PHYS_SDRAM_1 && start <= ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)) {
				gd->bd->bi_dram[i].start = start;

				if ((end + 1) <= ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))
					gd->bd->bi_dram[i].size = end - start + 1;
				else
					gd->bd->bi_dram[i].size = PHYS_SDRAM_1_SIZE;

				dram_bank_sort(i);
				i++;
			} else if (start >= PHYS_SDRAM_2 && start <= ((sc_faddr_t)PHYS_SDRAM_2 + PHYS_SDRAM_2_SIZE)) {
				gd->bd->bi_dram[i].start = start;

				if ((end + 1) <= ((sc_faddr_t)PHYS_SDRAM_2 + PHYS_SDRAM_2_SIZE))
					gd->bd->bi_dram[i].size = end - start + 1;
				else
					gd->bd->bi_dram[i].size = PHYS_SDRAM_2_SIZE;

				dram_bank_sort(i);
				i++;
			}

		}
	}

	/* If error, set to the default value */
	if (!i) {
		gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
		gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;
		gd->bd->bi_dram[1].start = PHYS_SDRAM_2;
		gd->bd->bi_dram[1].size = PHYS_SDRAM_2_SIZE;
	}
}

static u64 get_block_attrs(sc_faddr_t addr_start)
{
	if ((addr_start >= PHYS_SDRAM_1 && addr_start <= ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))
		|| (addr_start >= PHYS_SDRAM_2 && addr_start <= ((sc_faddr_t)PHYS_SDRAM_2 + PHYS_SDRAM_2_SIZE)))
		return (PTE_BLOCK_MEMTYPE(MT_NORMAL) | PTE_BLOCK_OUTER_SHARE);

	return (PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) | PTE_BLOCK_NON_SHARE | PTE_BLOCK_PXN | PTE_BLOCK_UXN);
}

static u64 get_block_size(sc_faddr_t addr_start, sc_faddr_t addr_end)
{
	if (addr_start >= PHYS_SDRAM_1 && addr_start <= ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)) {
		if ((addr_end + 1) > ((sc_faddr_t)PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))
			return PHYS_SDRAM_1_SIZE;

	} else if (addr_start >= PHYS_SDRAM_2 && addr_start <= ((sc_faddr_t)PHYS_SDRAM_2 + PHYS_SDRAM_2_SIZE)) {

		if ((addr_end + 1) > ((sc_faddr_t)PHYS_SDRAM_2 + PHYS_SDRAM_2_SIZE))
			return PHYS_SDRAM_2_SIZE;
	}

	return (addr_end - addr_start + 1);
}

#define MAX_PTE_ENTRIES 512
#define MAX_MEM_MAP_REGIONS 16

static struct mm_region imx8_mem_map[MAX_MEM_MAP_REGIONS];
struct mm_region *mem_map = imx8_mem_map;

void enable_caches(void)
{
	sc_rm_mr_t mr;
	sc_faddr_t start, end;
	int err, i;

	/* Create map for registers access from 0x1c000000 to 0x80000000*/
	imx8_mem_map[0].virt = 0x1c000000UL;
	imx8_mem_map[0].phys = 0x1c000000UL;
	imx8_mem_map[0].size = 0x64000000UL;
	imx8_mem_map[0].attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE | PTE_BLOCK_PXN | PTE_BLOCK_UXN;

	i = 1;
	for (mr = 0; mr < 64 && i < MAX_MEM_MAP_REGIONS; mr++) {
		err = get_owned_memreg(mr, &start, &end);
		if (!err) {
			imx8_mem_map[i].virt = start;
			imx8_mem_map[i].phys = start;
			imx8_mem_map[i].size = get_block_size(start, end);
			imx8_mem_map[i].attrs = get_block_attrs(start);
			i++;
		}
	}

	if (i < MAX_MEM_MAP_REGIONS) {
		imx8_mem_map[i].size = 0;
		imx8_mem_map[i].attrs = 0;
	} else {
		printf("Error, need more MEM MAP REGIONS reserved\n");
		icache_enable();
		return;
	}

	for (i = 0;i < MAX_MEM_MAP_REGIONS;i++) {
		debug("[%d] vir = 0x%llx phys = 0x%llx size = 0x%llx attrs = 0x%llx\n", i,
			imx8_mem_map[i].virt, imx8_mem_map[i].phys, imx8_mem_map[i].size, imx8_mem_map[i].attrs);
	}

	icache_enable();
	dcache_enable();
}

#ifndef CONFIG_SYS_DCACHE_OFF
u64 get_page_table_size(void)
{
	u64 one_pt = MAX_PTE_ENTRIES * sizeof(u64);
	u64 size = 0;

	/* For each memory region, the max table size:  2 level 3 tables + 2 level 2 tables + 1 level 1 table*/
	size = (2 + 2 + 1) * one_pt * MAX_MEM_MAP_REGIONS + one_pt;

	/*
	 * We need to duplicate our page table once to have an emergency pt to
	 * resort to when splitting page tables later on
	 */
	size *= 2;

	/*
	 * We may need to split page tables later on if dcache settings change,
	 * so reserve up to 4 (random pick) page tables for that.
	 */
	size += one_pt * 4;

	return size;
}
#endif

static bool check_device_power_off(struct udevice *dev,
	const char* permanent_on_devices[], int size)
{
	int i;

	for (i = 0; i < size; i++) {
		if (!strcmp(dev->name, permanent_on_devices[i]))
			return false;
	}

	return true;
}

void power_off_pd_devices(const char* permanent_on_devices[], int size)
{
	struct udevice *dev;
	struct power_domain pd;

	for (uclass_find_first_device(UCLASS_POWER_DOMAIN, &dev); dev;
		uclass_find_next_device(&dev)) {

		if (device_active(dev)) {
			/* Power off active pd devices except the permanent power on devices */
			if (check_device_power_off(dev, permanent_on_devices, size)) {
				pd.dev = dev;
				power_domain_off(&pd);
			}
		}
	}
}
