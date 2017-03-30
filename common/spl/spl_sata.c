/*
 * (C) Copyright 2013
 * Texas Instruments, <www.ti.com>
 *
 * Dan Murphy <dmurphy@ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * Derived work from spl_usb.c
 */

#include <common.h>
#include <spl.h>
#include <asm/u-boot.h>
#include <sata.h>
#include <scsi.h>
#include <errno.h>
#include <fat.h>
#include <image.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_ADVANTECH
static int spl_sata_check_crc(unsigned int dev)
{
        u32 n;
        /* read crc file */
        char tag[512];
        char crc[512];

        n = sata_read(dev, 0x02, 1, (void *) 0x22100000);
        if(n != 1)
                return 1;

        memcpy(tag, (void *) 0x22100000, 512);
        //tag[9] = '\0';
        //printf("crc file %s\n", tag);

        /* make uboot crc */
        n = sata_read(dev, 0x03, 0x4b0, (void *) 0x22000000);
        if(n != 0x4b0)
                return 1;

        *(int *)0x21f00000 = crc32 (0, (const uchar *) 0x22000000, 0x96000);
        sprintf(crc, "%08x", *(int *)0x21f00000);
        //crc[9] = '\0';
        //printf("uboot crc %s\n", crc);

        /* verrify crc */
        if(memcmp(tag, crc, 8))
        {
                printf("spl: sata dev %d - crc error\n", dev);
                return 1;
        }

        return 0;
}
#endif

static int spl_sata_load_image(struct spl_image_info *spl_image,
			       struct spl_boot_device *bootdev)
{
	int err;
	struct blk_desc *stor_dev;

	err = init_sata(CONFIG_SPL_SATA_BOOT_DEVICE);
	if (err) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		printf("spl: sata init failed: err - %d\n", err);
#endif
		return err;
	} else {
		/* try to recognize storage devices immediately */
		scsi_scan(0);
		stor_dev = blk_get_devnum_by_type(IF_TYPE_SCSI, 0);
		if (!stor_dev)
			return -ENODEV;
	}
#ifdef CONFIG_ADVANTECH
        err = spl_sata_check_crc(CONFIG_SPL_SATA_BOOT_DEVICE);
        if (err) 
                return err;
#endif

#ifdef CONFIG_SPL_OS_BOOT
	if (spl_start_uboot() ||
	    spl_load_image_fat_os(spl_image, stor_dev,
				  CONFIG_SYS_SATA_FAT_BOOT_PARTITION))
#endif
	{
		err = spl_load_image_fat(spl_image, stor_dev,
					CONFIG_SYS_SATA_FAT_BOOT_PARTITION,
				CONFIG_SPL_FS_LOAD_PAYLOAD_NAME);
	}
	if (err) {
		puts("Error loading sata device\n");
		return err;
	}

	return 0;
}
SPL_LOAD_IMAGE_METHOD("SATA", 0, BOOT_DEVICE_SATA, spl_sata_load_image);
