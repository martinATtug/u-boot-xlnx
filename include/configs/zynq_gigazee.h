/*
 * (C) Copyright 2013 Trenz-Electronics GmbH
 *
 * Configuration for TE0720 GigaZee Board
 * See zynq_common.h for Zynq common configs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_ZYNQ_GIGAZEE_H
#define __CONFIG_ZYNQ_GIGAZEE_H

#define PHYS_SDRAM_1_SIZE (1024 * 1024 * 1024)

#define CONFIG_ZYNQ_SERIAL_UART0
#define CONFIG_ZYNQ_GEM0
#define CONFIG_PHY_ADDR	0

#define CONFIG_SYS_NO_FLASH

#define CONFIG_MMC
#define CONFIG_ZYNQ_SPI

#include <configs/zynq_common.h>

#undef	SD_BASEADDR
#define SD_BASEADDR			0xE0101000

#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"machid=0x00000d32\0"	\
	"ethaddr=00:0a:35:00:01:22\0"	\
	"ipaddr=192.168.42.20\0" \
	"serverip=192.168.42.2\0" \
	"kernel_image=zImage\0"	\
	"ramdisk_image=ramdisk.image.gz\0"	\
	"devicetree_image=devicetree.dtb\0"	\
	"bitstream_image=system.bit.bin\0"	\
	"kernel_addr=0x8000\0" \
	"devicetree_addr=0x1000000\0" \
	"ramdisk_addr=0x800000\0" \
	"kernel_offset=0x450000\0" \
	"devicetree_offset=0x950000\0" \
	"ramdisk_offset=0x970000\0" \
	"kernel_size=0x500000\0" \
	"devicetree_size=0x20000\0" \
	"ramdisk_size=0x5E0000\0" \
	"qspiboot=echo Copying Linux from SPI to RAM... && " \
		"sf probe 0 0 0 && " \
		"sf read ${kernel_addr} ${kernel_offset} ${kernel_size} && " \
		"sf read ${devicetree_addr} ${devicetree_offset} ${devicetree_size} && " \
		"sf read ${ramdisk_addr} ${ramdisk_offset} ${ramdisk_size} && " \
		"go ${kernel_addr}\0"	\
	"sdboot=echo Copying Linux from SD to RAM... && " \
		"mmcinfo && " \
		"fatload mmc 0 ${kernel_addr} ${kernel_image} && " \
		"fatload mmc 0 ${devicetree_addr} ${devicetree_image} && " \
		"fatload mmc 0 ${ramdisk_addr} ${ramdisk_image} && " \
		"go ${kernel_addr}\0"	\
	"fetch=echo Downloading Linux via TFTP... && " \
		"tftp ${kernel_addr} ${kernel_image} && " \
		"tftp ${devicetree_addr} ${devicetree_image} && " \
		"tftp ${ramdisk_addr} ${ramdisk_image}\0" \
	"reflash=echo Write from RAM to SPI... && " \
		"sf probe && " \
		"sf update ${kernel_addr} ${kernel_offset} ${kernel_size} && " \
		"sf update ${devicetree_addr} ${devicetree_offset} ${devicetree_size} && " \
		"sf update ${ramdisk_addr} ${ramdisk_offset} ${ramdisk_size}\0" \
	"linux=echo Booting Linux... && " \
		"go ${kernel_addr}\0"


#endif /* __CONFIG_ZYNQ_GIGAZEE_H */
