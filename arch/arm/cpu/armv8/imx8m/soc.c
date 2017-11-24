/* Copyright 2017 NXP
 *
 * Peng Fan <peng.fan@nxp.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <asm/arch/imx-regs.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/sys_proto.h>
#include <asm/imx-common/hab.h>
#include <asm/imx-common/boot_mode.h>
#include <asm/armv8/mmu.h>
#include <errno.h>
#include <fdt_support.h>
#include <fsl_wdog.h>

DECLARE_GLOBAL_DATA_PTR;

#if defined(CONFIG_SECURE_BOOT)
struct imx_sec_config_fuse_t const imx_sec_config_fuse = {
	.bank = 1,
	.word = 3,
};
#endif

/*
 * OCOTP_TESTER3[9:8] (see Fusemap Description Table offset 0x440)
 * defines a 2-bit SPEED_GRADING
 */
#define OCOTP_TESTER3_SPEED_SHIFT	8
#define OCOTP_TESTER3_SPEED_800MHZ	0
#define OCOTP_TESTER3_SPEED_1GHZ	1
#define OCOTP_TESTER3_SPEED_1300HZ	2
#define OCOTP_TESTER3_SPEED_1500HZ	3

u32 get_cpu_speed_grade_hz(void)
{
	struct ocotp_regs *ocotp = (struct ocotp_regs *)OCOTP_BASE_ADDR;
	struct fuse_bank *bank = &ocotp->bank[1];
	struct fuse_bank1_regs *fuse =
		(struct fuse_bank1_regs *)bank->fuse_regs;
	uint32_t val;

	val = readl(&fuse->tester3);
	val >>= OCOTP_TESTER3_SPEED_SHIFT;
	val &= 0x3;

	switch(val) {
	case OCOTP_TESTER3_SPEED_800MHZ:
		return 800000000;
	case OCOTP_TESTER3_SPEED_1GHZ:
		return 1000000000;
	case OCOTP_TESTER3_SPEED_1300HZ:
		return 1300000000;
	case OCOTP_TESTER3_SPEED_1500HZ:
		return 1500000000;
	}
	return 0;
}

/*
 * OCOTP_TESTER3[7:6] (see Fusemap Description Table offset 0x440)
 * defines a 2-bit SPEED_GRADING
 */
#define OCOTP_TESTER3_TEMP_SHIFT	6

/* CPU Temperature Grades */
#define TEMP_COMMERCIAL         0
#define TEMP_EXTCOMMERCIAL      1
#define TEMP_INDUSTRIAL         2
#define TEMP_AUTOMOTIVE         3


u32 get_cpu_temp_grade(int *minc, int *maxc)
{
	struct ocotp_regs *ocotp = (struct ocotp_regs *)OCOTP_BASE_ADDR;
	struct fuse_bank *bank = &ocotp->bank[1];
	struct fuse_bank1_regs *fuse =
		(struct fuse_bank1_regs *)bank->fuse_regs;
	uint32_t val;

	val = readl(&fuse->tester3);
	val >>= OCOTP_TESTER3_TEMP_SHIFT;
	val &= 0x3;

	if (minc && maxc) {
		if (val == TEMP_AUTOMOTIVE) {
			*minc = -40;
			*maxc = 125;
		} else if (val == TEMP_INDUSTRIAL) {
			*minc = -40;
			*maxc = 105;
		} else if (val == TEMP_EXTCOMMERCIAL) {
			*minc = -20;
			*maxc = 105;
		} else {
			*minc = 0;
			*maxc = 95;
		}
	}
	return val;
}

int timer_init(void)
{
#ifdef CONFIG_SPL_BUILD
	void __iomem *sctr_base = (void __iomem *)SCTR_BASE_ADDR;
	unsigned long freq;
	u32 val;

	freq = readl(sctr_base + CNTFID0_OFF);

	/* Update with accurate clock frequency */
	asm volatile("msr cntfrq_el0, %0" : : "r" (freq) : "memory");

	val = readl(sctr_base + CNTCR_OFF);
	val &= ~(SC_CNTCR_FREQ0 | SC_CNTCR_FREQ1);
	val |= SC_CNTCR_FREQ0 | SC_CNTCR_ENABLE | SC_CNTCR_HDBG;
	writel(val, sctr_base + CNTCR_OFF);
#endif

	gd->arch.tbl = 0;
	gd->arch.tbu = 0;

	return 0;
}

void enable_tzc380(void)
{
	u32 val;

	/* Enable TZASC and lock setting */
	val = readl(IOMUXC_GPR10);
	val |= GPR_TZASC_EN;
	writel(val, IOMUXC_GPR10);
	val |= GPR_TZASC_EN_LOCK;
	writel(val, IOMUXC_GPR10);
}

void set_wdog_reset(struct wdog_regs *wdog)
{
	u32 reg = readw(&wdog->wcr);
	/*
	 * Output WDOG_B signal to reset external pmic or POR_B decided by
	 * the board desgin. Without external reset, the peripherals/DDR/
	 * PMIC are not reset, that may cause system working abnormal.
	 */
	reg = readw(&wdog->wcr);
	reg |= 1 << 3;
	/*
	 * WDZST bit is write-once only bit. Align this bit in kernel,
	 * otherwise kernel code will have no chance to set this bit.
	 */
	reg |= 1 << 0;
	writew(reg, &wdog->wcr);
}

static struct mm_region imx8m_mem_map[] = {
	{
		.virt = 0x0UL,
		.phys = 0x0UL,
		.size = 0x100000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_OUTER_SHARE
	}, {
		.virt = 0x100000UL,
		.phys = 0x100000UL,
		.size = 0x8000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = 0x7C0000UL,
		.phys = 0x7C0000UL,
		.size = 0x80000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = 0x900000UL,
		.phys = 0x900000UL,
		.size = 0x200000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_OUTER_SHARE
	}, {
		.virt = 0xB00000UL,
		.phys = 0xB00000UL,
		.size = 0x3f500000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
			 PTE_BLOCK_NON_SHARE |
			 PTE_BLOCK_PXN | PTE_BLOCK_UXN
	}, {
		.virt = 0x40000000UL,
		.phys = 0x40000000UL,
		.size = 0xC0000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_OUTER_SHARE
	}, {
		.virt = 0x100000000UL,
		.phys = 0x100000000UL,
		.size = 0x040000000UL,
		.attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
			 PTE_BLOCK_OUTER_SHARE
	}, {
		/* List terminator */
		0,
	}
};
struct mm_region *mem_map = imx8m_mem_map;

u32 get_cpu_rev(void)
{
	u32 reg = readl((void __iomem *)DIGPROG);
	u32 type = (reg >> 16) & 0xff;

	reg &= 0xff;

	if (reg == 0x10) {
		/* For B0 chip, the DIGPROG is not updated, still TO1.0.
		 * we have to check ROM version further
		 */
		uint32_t rom_version;
		rom_version = readl((void __iomem *)0x800);
		if (rom_version != 0x10) {
			rom_version = readl((void __iomem *)0x83c);
			if (rom_version >= 0x20)
				reg = 0x20;
		}
	}

	return (type << 12) | reg;
}

void imx_set_wdog_powerdown(bool enable)
{
	struct wdog_regs *wdog1 = (struct wdog_regs *)WDOG1_BASE_ADDR;
	struct wdog_regs *wdog2 = (struct wdog_regs *)WDOG2_BASE_ADDR;
	struct wdog_regs *wdog3 = (struct wdog_regs *)WDOG3_BASE_ADDR;

	/* Write to the PDE (Power Down Enable) bit */
	writew(enable, &wdog1->wmcr);
	writew(enable, &wdog2->wmcr);
	writew(enable, &wdog3->wmcr);
}

int arch_cpu_init(void)
{
	/*
	 * Init timer at very early state, because sscg pll setting
	 * will use it
	 */
	timer_init();
	clock_init();

	imx_set_wdog_powerdown(false);

	return 0;
}

#if defined(CONFIG_FEC_MXC)
void imx_get_mac_from_fuse(int dev_id, unsigned char *mac)
{
	struct ocotp_regs *ocotp = (struct ocotp_regs *)OCOTP_BASE_ADDR;
	struct fuse_bank *bank = &ocotp->bank[9];
	struct fuse_bank9_regs *fuse =
		(struct fuse_bank9_regs *)bank->fuse_regs;

	u32 value = readl(&fuse->mac_addr1);
	mac[0] = (value >> 8);
	mac[1] = value;

	value = readl(&fuse->mac_addr0);
	mac[2] = value >> 24;
	mac[3] = value >> 16;
	mac[4] = value >> 8;
	mac[5] = value;
}
#endif

#ifdef CONFIG_IMX_BOOTAUX
#define FSL_SIP_SRC		0xC2000005
#define FSL_SIP_SRC_M4_START	0x00
#define FSL_SIP_SRC_M4_STARTED	0x01
int arch_auxiliary_core_up(u32 core_id, ulong boot_private_data)
{
	u32 stack, pc;

	if (!boot_private_data)
		return -EINVAL;

	stack = *(u32 *)boot_private_data;
	pc = *(u32 *)(boot_private_data + 4);

	/* Set the stack and pc to M4 bootROM */
	writel(stack, M4_BOOTROM_BASE_ADDR);
	writel(pc, M4_BOOTROM_BASE_ADDR + 4);

	/* Enable M4 */
	call_imx_sip(FSL_SIP_SRC, FSL_SIP_SRC_M4_START, 0, 0);

	return 0;
}

int arch_auxiliary_core_check_up(u32 core_id)
{
	return call_imx_sip(FSL_SIP_SRC, FSL_SIP_SRC_M4_STARTED, 0, 0);
}
#endif

enum boot_device get_boot_device(void)
{
	struct bootrom_sw_info **p =
		is_soc_rev(CHIP_REV_1_0)? (struct bootrom_sw_info **)ROM_SW_INFO_ADDR_A0 :
		(struct bootrom_sw_info **)ROM_SW_INFO_ADDR;

	enum boot_device boot_dev = SD1_BOOT;
	u8 boot_type = (*p)->boot_dev_type;
	u8 boot_instance = (*p)->boot_dev_instance;

	switch (boot_type) {
	case BOOT_TYPE_SD:
		boot_dev = boot_instance + SD1_BOOT;
		break;
	case BOOT_TYPE_MMC:
		boot_dev = boot_instance + MMC1_BOOT;
		break;
	case BOOT_TYPE_NAND:
		boot_dev = NAND_BOOT;
		break;
	case BOOT_TYPE_QSPI:
		boot_dev = QSPI_BOOT;
		break;
	case BOOT_TYPE_WEIM:
		boot_dev = WEIM_NOR_BOOT;
		break;
	case BOOT_TYPE_SPINOR:
		boot_dev = SPI_NOR_BOOT;
		break;
	case BOOT_TYPE_USB:
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

#ifdef CONFIG_ENV_IS_IN_MMC
__weak int board_mmc_get_env_dev(int devno)
{
	return CONFIG_SYS_MMC_ENV_DEV;
}

int mmc_get_env_dev(void)
{
	struct bootrom_sw_info **p =
		is_soc_rev(CHIP_REV_1_0)? (struct bootrom_sw_info **)ROM_SW_INFO_ADDR_A0 :
		(struct bootrom_sw_info **)ROM_SW_INFO_ADDR;
	int devno = (*p)->boot_dev_instance;
	u8 boot_type = (*p)->boot_dev_type;

	/* If not boot from sd/mmc, use default value */
	if ((boot_type != BOOT_TYPE_SD) && (boot_type != BOOT_TYPE_MMC))
		return CONFIG_SYS_MMC_ENV_DEV;

	return board_mmc_get_env_dev(devno);
}
#endif

#ifdef CONFIG_SERIAL_TAG
void get_board_serial(struct tag_serialnr *serialnr)
{
	struct ocotp_regs *ocotp = (struct ocotp_regs *)OCOTP_BASE_ADDR;
	struct fuse_bank *bank = &ocotp->bank[0];
	struct fuse_bank0_regs *fuse =
		(struct fuse_bank0_regs *)bank->fuse_regs;

	serialnr->low = fuse->uid_low;
	serialnr->high = fuse->uid_high;
}
#endif

#ifdef CONFIG_OF_SYSTEM_SETUP
static int ft_add_optee_node(void *fdt, bd_t *bd)
{
	const char *path, *subpath;
	int offs;

	/*
	 * No TEE space allocated indicating no TEE running, so no
	 * need to add optee node in dts
	 */
	if (!rom_pointer[1])
		return 0;

	offs = fdt_increase_size(fdt, 512);
	if (offs) {
		printf("No Space for dtb\n");
		return 1;
	}

	path = "/firmware";
	offs = fdt_path_offset(fdt, path);
	if (offs < 0) {
		path = "/";
		offs = fdt_path_offset(fdt, path);

		if (offs < 0) {
			printf("Could not find root node.\n");
			return 1;
		}

		subpath = "firmware";
		offs = fdt_add_subnode(fdt, offs, subpath);
		if (offs < 0) {
			printf("Could not create %s node.\n", subpath);
		}
	}

	subpath = "optee";
	offs = fdt_add_subnode(fdt, offs, subpath);
	if (offs < 0) {
		printf("Could not create %s node.\n", subpath);
	}

	fdt_setprop_string(fdt, offs, "compatible", "linaro,optee-tz");
	fdt_setprop_string(fdt, offs, "method", "smc");

	return 0;
}

int ft_system_setup(void *blob, bd_t *bd)
{
	if (get_boot_device() == USB_BOOT) {
		const char *nodes_path[] = {
			"/dcss@32e00000",
			"/hdmi@32c00000",
			"/hdmi_cec@32c33800",
			"/hdmi_drm@32c00000",
			"/display-subsystem",
			"/sound-hdmi"
		};

		int i = 0;
		int rc;
		int nodeoff;
		const char *status = "disabled";

		for (i = 0; i < ARRAY_SIZE(nodes_path); i++) {
			nodeoff = fdt_path_offset(blob, nodes_path[i]);
			if (nodeoff < 0)
				continue; /* Not found, skip it */

			printf("Found %s node\n", nodes_path[i]);

add_status:
			rc = fdt_setprop(blob, nodeoff, "status", status, strlen(status) + 1);
			if (rc) {
				if (rc == -FDT_ERR_NOSPACE) {
					rc = fdt_increase_size(blob, 512);
					if (!rc)
						goto add_status;
				}
				printf("Unable to update property %s:%s, err=%s\n",
					nodes_path[i], "status", fdt_strerror(rc));
			} else {
				printf("Modify %s:%s disabled\n",
					nodes_path[i], "status");
			}
		}

		const char *usb_dwc3_path = "/usb@38100000/dwc3";
		nodeoff = fdt_path_offset(blob, usb_dwc3_path);
		if (nodeoff >= 0) {
			const char *speed = "high-speed";
			printf("Found %s node\n", usb_dwc3_path);

usb_modify_speed:

			rc = fdt_setprop(blob, nodeoff, "maximum-speed", speed, strlen(speed) + 1);
			if (rc) {
				if (rc == -FDT_ERR_NOSPACE) {
					rc = fdt_increase_size(blob, 512);
					if (!rc)
						goto usb_modify_speed;
				}
				printf("Unable to set property %s:%s, err=%s\n",
					usb_dwc3_path, "maximum-speed", fdt_strerror(rc));
			} else {
				printf("Modify %s:%s = %s\n",
					usb_dwc3_path, "maximum-speed", speed);
			}
		}else {
			printf("Can't found %s node\n", usb_dwc3_path);
		}
	}

	/* Disable the CPU idle for A0 chip since the HW does not support it */
	if (is_soc_rev(CHIP_REV_1_0)) {
		const char *nodes_path[] = {
			"/cpus/cpu@0",
			"/cpus/cpu@1",
			"/cpus/cpu@2",
			"/cpus/cpu@3",
		};

		int i = 0;
		int rc;
		int nodeoff;

		for (i = 0; i < ARRAY_SIZE(nodes_path); i++) {
			nodeoff = fdt_path_offset(blob, nodes_path[i]);
			if (nodeoff < 0)
				continue; /* Not found, skip it */

			printf("Found %s node\n", nodes_path[i]);

			rc = fdt_delprop(blob, nodeoff, "cpu-idle-states");
			if (rc) {
				printf("Unable to update property %s:%s, err=%s\n",
					nodes_path[i], "status", fdt_strerror(rc));
			} else {
				printf("Remove %s:%s\n",
					nodes_path[i], "cpu-idle-states");
			}
		}
	}

	return ft_add_optee_node(blob, bd);
}
#endif

void reset_cpu(ulong addr)
{
	struct watchdog_regs *wdog = (struct watchdog_regs *)WDOG1_BASE_ADDR;

	/* Clear WDA to trigger WDOG_B immediately */
	writew((WCR_WDE | WCR_SRS), &wdog->wcr);

	while (1) {
		/*
		 * spin for .5 seconds before reset
		 */
	}
}
