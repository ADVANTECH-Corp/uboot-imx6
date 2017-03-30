/*
 * Copyright (C) 2014 Gateworks Corporation
 * Copyright (C) 2011-2012 Freescale Semiconductor, Inc.
 *
 * Author: Tim Harvey <tharvey@gateworks.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>
#include <asm/spl.h>
#include <spl.h>
#include <asm/imx-common/hab.h>

#ifdef CONFIG_ADVANTECH
extern const char version_string[];
#endif

#if defined(CONFIG_ADVANTECH) && defined(CONFIG_BOOT_SELECT)
#define SABRESD_NANDF_CS0       IMX_GPIO_NR(6, 11) //GPIO6_11
#define SABRESD_NANDF_CS1       IMX_GPIO_NR(6, 14) //GPIO6_14
#define SABRESD_NANDF_CS2       IMX_GPIO_NR(6, 15) //GPIO6_15
#endif


#if defined(CONFIG_MX6)
/* determine boot device from SRC_SBMR1 (BOOT_CFG[4:1]) or SRC_GPR9 register */
u32 spl_boot_device(void)
{
#ifdef CONFIG_ADVANTECH
#ifdef CONFIG_BOOT_SELECT
        int board_cs0, board_cs1, board_cs2;

        gpio_request(SABRESD_NANDF_CS0, "Board_CS0");
        gpio_direction_input(SABRESD_NANDF_CS0);

        gpio_request(SABRESD_NANDF_CS1, "Board_CS1");
        gpio_direction_input(SABRESD_NANDF_CS1);

        gpio_request(SABRESD_NANDF_CS2, "Board_CS2");
        gpio_direction_input(SABRESD_NANDF_CS2);

        board_cs0 = gpio_get_value(SABRESD_NANDF_CS0);
        board_cs1 = gpio_get_value(SABRESD_NANDF_CS1);

        board_cs2 = gpio_get_value(SABRESD_NANDF_CS2);

        printf("Boot_Switch: cs0=%d,cs1=%d,cs2=%d\n",board_cs0,board_cs1,board_cs2);
        //--------------------------------------------------------------------

        if((!board_cs2)&&(!board_cs1)&&(!board_cs0))            //Carrier SATA//
        {
                printf("booting from Carrier SATA\n");
                *(int *)0x22200000 = 0x02;

                return	BOOT_DEVICE_SATA;
        }
        else if((!board_cs2)&&(!board_cs1)&&(board_cs0))        //Carrier SD Card//
        {
                printf("booting from Carrier SD Card\n");
                *(int *)0x22200000 = 0x01;

                return	BOOT_DEVICE_MMC1;
        }
        else if((!board_cs2)&&(board_cs1)&&(!board_cs0))        //Carrier eMMC Flash//
        {
                printf("booting from Carrier eMMC Flash\n");
        }
        else if((!board_cs2)&&(board_cs1)&&(board_cs0))         //Carrier SPI//
        {
                printf("booting from Carrier SPI\n");
                *(int *)0x22200000 = 0x04;

                return	BOOT_DEVICE_SPI;
        }
        else if((board_cs2)&&(!board_cs1)&&(!board_cs0))        //Module device//
        {
                printf("booting from Module device\n");
        }
        else if((board_cs2)&&(!board_cs1)&&(board_cs0))         //Remote boot//
        {
                printf("booting from Remote boot\n");
        }
        else if((board_cs2)&&(board_cs1)&&(!board_cs0))         //Module eMMC Flash//
        {
                printf("booting from Module eMMC Flash\n");
                *(int *)0x22200000 = 0x03;

                return BOOT_DEVICE_MMC2;
        }
        else if((board_cs2)&&(board_cs1)&&(board_cs0))          //Module SPI//
        {
                printf("booting from Module SPI\n");
        }
        else
        {
                printf("booting not support\n");
        }
        //--------------------------------------------------------------------
#else
        /* We use BOOT_DEVICE_AUTO for auto boot device selection */
        return BOOT_DEVICE_AUTO;
#endif
#else

	struct src *psrc = (struct src *)SRC_BASE_ADDR;
	unsigned int gpr10_boot = readl(&psrc->gpr10) & (1 << 28);
	unsigned reg = gpr10_boot ? readl(&psrc->gpr9) : readl(&psrc->sbmr1);
	unsigned int bmode = readl(&psrc->sbmr2);

	/*
	 * Check for BMODE if serial downloader is enabled
	 * BOOT_MODE - see IMX6DQRM Table 8-1
	 */
	if (((bmode >> 24) & 0x03) == 0x01) /* Serial Downloader */
		return BOOT_DEVICE_UART;
	/* BOOT_CFG1[7:4] - see IMX6DQRM Table 8-8 */
	switch ((reg & 0x000000FF) >> 4) {
	 /* EIM: See 8.5.1, Table 8-9 */
	case 0x0:
		/* BOOT_CFG1[3]: NOR/OneNAND Selection */
		if ((reg & 0x00000008) >> 3)
			return BOOT_DEVICE_ONENAND;
		else
			return BOOT_DEVICE_NOR;
		break;
	/* Reserved: Used to force Serial Downloader */
	case 0x1:
		return BOOT_DEVICE_UART;
	/* SATA: See 8.5.4, Table 8-20 */
	case 0x2:
		return BOOT_DEVICE_SATA;
	/* Serial ROM: See 8.5.5.1, Table 8-22 */
	case 0x3:
		/* BOOT_CFG4[2:0] */
		switch ((reg & 0x07000000) >> 24) {
		case 0x0 ... 0x4:
			return BOOT_DEVICE_SPI;
		case 0x5 ... 0x7:
			return BOOT_DEVICE_I2C;
		}
		break;
	/* SD/eSD: 8.5.3, Table 8-15  */
	case 0x4:
	case 0x5:
		return BOOT_DEVICE_MMC1;
	/* MMC/eMMC: 8.5.3 */
	case 0x6:
	case 0x7:
		return BOOT_DEVICE_MMC1;
	/* NAND Flash: 8.5.2 */
	case 0x8 ... 0xf:
		return BOOT_DEVICE_NAND;
	}
	return BOOT_DEVICE_NONE;
#endif	//CONFIG_ADVANTECH
}
#endif

#if defined(CONFIG_SPL_MMC_SUPPORT)
/* called from spl_mmc to see type of boot mode for storage (RAW or FAT) */
u32 spl_boot_mode(const u32 boot_device)
{
	switch (spl_boot_device()) {
	/* for MMC return either RAW or FAT mode */
	case BOOT_DEVICE_MMC1:
	case BOOT_DEVICE_MMC2:
#if defined(CONFIG_ADVANTECH)
	case BOOT_DEVICE_AUTO:
#endif
#if defined(CONFIG_SPL_FAT_SUPPORT)
		return MMCSD_MODE_FS;
#elif defined(CONFIG_SUPPORT_EMMC_BOOT)
		return MMCSD_MODE_EMMCBOOT;
#else
		return MMCSD_MODE_RAW;
#endif
		break;
	default:
		puts("spl: ERROR:  unsupported device\n");
		hang();
	}
}
#endif

#if defined(CONFIG_SECURE_BOOT)

__weak void __noreturn jump_to_image_no_args(struct spl_image_info *spl_image)
{
	typedef void __noreturn (*image_entry_noargs_t)(void);

	image_entry_noargs_t image_entry =
		(image_entry_noargs_t)(unsigned long)spl_image->entry_point;

	debug("image entry point: 0x%lX\n", spl_image->entry_point);

	/* HAB looks for the CSF at the end of the authenticated data therefore,
	 * we need to subtract the size of the CSF from the actual filesize */
	if (authenticate_image(spl_image->load_addr,
			       spl_image->size - CONFIG_CSF_SIZE)) {
		image_entry();
	} else {
		puts("spl: ERROR:  image authentication unsuccessful\n");
		hang();
	}
}

#endif

#ifdef CONFIG_SPL_BOARD_INIT
void spl_board_init(void)
{
        char *pch,*s;
        char tmp[256];

        /* log adv version */
        pch=strchr(version_string,'2');
        if (pch!=NULL)
        {
                s=strchr(pch,' ');
                strncpy(tmp, pch, s-pch);
                tmp[s-pch]='\0';
                strcpy((void *)0x22300000, tmp);
        }

        /* forword memory size to uboot */
        *(unsigned int *)0x22400000 = PHYS_SDRAM_SIZE;

        /* record ddr bit, 32 or 64 bit */
#ifdef CONFIG_DDR_32BIT
        *(unsigned int *)0x22500000 = 32;
#else
        *(unsigned int *)0x22500000 = 64;
#endif
}
#endif

