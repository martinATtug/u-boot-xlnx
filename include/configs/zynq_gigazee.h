/*
 * Trenz Electronics 
 *
 * Configuration for Zynq Evaluation and Development Board - TE0720
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
#define CONFIG_ZYNQ_I2C

#include <configs/zynq_common.h>

#undef CONFIG_IPADDR
#define CONFIG_IPADDR   192.168.42.50
#undef CONFIG_SERVERIP
#define CONFIG_SERVERIP 192.168.42.2
#undef SD_BASEADDR
#define SD_BASEADDR     0xE0101000
#undef CONFIG_ZYNQ_I2C_CTLR_0
#define CONFIG_ZYNQ_I2C_CTLR_1

#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"ethaddr=00:0a:35:00:01:22\0"	\
	"kernel_image=uImage\0"	\
	"ramdisk_image=uramdisk.image.gz\0"	\
	"devicetree_image=devicetree.dtb\0"	\
	"bitstream_image=system.bit.bin\0"	\
	"loadbit_addr=0x100000\0"	\
	"kernel_size=0x500000\0"	\
	"devicetree_size=0x20000\0"	\
	"ramdisk_size=0x5E0000\0"	\
	"fdt_high=0x20000000\0"	\
	"initrd_high=0x20000000\0"	\
	"kerel_offset=0x450000\0" \
	"qspiboot=echo Copying Linux from QSPI flash to RAM... && " \
		"sf probe 0 0 0 && " \
		"sf read 0x3000000 0x450000 ${kernel_size} && " \
		"sf read 0x2A00000 0x950000 ${devicetree_size} && " \
		"sf read 0x2000000 0x970000 ${ramdisk_size} && " \
		"bootm 0x3000000 0x2000000 0x2A00000\0" \
	"sdboot=echo Copying Linux from SD to RAM... && " \
		"mmcinfo && " \
		"fatload mmc 0 0x3000000 ${kernel_image} && " \
		"fatload mmc 0 0x2A00000 ${devicetree_image} && " \
		"fatload mmc 0 0x2000000 ${ramdisk_image} && " \
		"bootm 0x3000000 0x2000000 0x2A00000\0" \
	"fetch=echo TFTPing Linux to RAM... && " \
		"tftp 0x3000000 ${kernel_image} && " \
		"tftp 0x2A00000 ${devicetree_image} && " \
		"tftp 0x2000000 ${ramdisk_image}\0" \
	"reflash=echo Write Linux from RAM to QSPI flash... && " \
		"sf probe 0 0 0 && " \
		"sf update 0x3000000 0x450000 ${kernel_size} && " \
		"sf update 0x2A00000 0x950000 ${devicetree_size} && " \
		"sf update 0x2000000 0x970000 ${ramdisk_size}\0" \
	"linux=bootm 0x3000000 0x2000000 0x2A00000\0" \
	"tftpboot=echo TFTPing Linux to RAM... && " \
		"tftp 0x3000000 ${kernel_image} && " \
		"tftp 0x2A00000 ${devicetree_image} && " \
		"tftp 0x2000000 ${ramdisk_image} && " \
		"bootm 0x3000000 0x2000000 0x2A00000\0"

/*
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"ethaddr=00:0a:35:00:01:22\0"	\
	"kernel_image=uImage\0"	\
	"ramdisk_image=uramdisk.image.gz\0"	\
	"devicetree_image=devicetree.dtb\0"	\
	"bitstream_image=system.bit.bin\0"	\
	"kernel_size=0x500000\0"	\
	"devicetree_size=0x20000\0"	\
	"ramdisk_size=0x5E0000\0"	\
	"kernel_offset=0x450000\0" \
	"devicetree_offset=0x950000\0" \
	"ramdisk_offset=0x970000\0" \
	"kernel_addr=0x3000000\0"	\
	"devicetree_addr=0x2A00000\0"	\
	"ramdisk_addr=0x2000000\0"	\
	"qspiboot=echo Copying Linux from QSPI flash to RAM... && " \
		"sf probe 0 0 0 && " \
		"sf read ${kernel_addr} ${kernel_offset} ${kernel_size} && " \
		"sf read ${devicetree_addr} ${devicetree_offset} ${devicetree_size} && " \
		"echo Copying ramdisk... && " \
		"sf read ${ramdisk_addr} ${ramdisk_offset} ${ramdisk_size} && " \
		"bootm ${kernel_addr} ${ramdisk_addr} ${devicetree_addr}\0" \
	"sdboot=echo Copying Linux from SD to RAM... && " \
		"mmcinfo && " \
		"fatload mmc 0 ${kernel_addr} ${kernel_image} && " \
		"fatload mmc 0 ${devicetree_addr} ${devicetree_image} && " \
		"fatload mmc 0 ${ramdisk_addr} ${ramdisk_image} && " \
		"bootm ${kernel_addr} ${ramdisk_addr} ${devicetree_addr}\0" \
	"fetch=echo TFTPing Linux to RAM... && " \
		"tftp ${kernel_addr} ${kernel_image} && " \
		"tftp ${devicetree_addr} ${devicetree_image} && " \
		"tftp ${ramdisk_addr} ${ramdisk_image}\0" \
	"reflash_all=echo Write from RAM to SPI... && " \
		"sf probe && " \
		"sf update ${kernel_addr} ${kernel_offset} ${kernel_size} && " \
		"sf update ${devicetree_addr} ${devicetree_offset} ${devicetree_size} && " \
		"sf update ${ramdisk_addr} ${ramdisk_offset} ${ramdisk_size}\0" \
	"reflash_dt=echo Write Devicetree from RAM to SPI... && " \
		"sf probe && " \
		"sf update ${devicetree_addr} ${devicetree_offset} ${devicetree_size}\0" \
	"linux=bootm ${kernel_addr} ${ramdisk_addr} ${devicetree_addr}\0"\
	"tftpboot=echo TFTPing Linux to RAM... && " \
		"tftp ${kernel_addr} ${kernel_image} && " \
		"tftp ${devicetree_addr} ${devicetree_image} && " \
		"tftp ${ramdisk_addr} ${ramdisk_image} && " \
		"bootm ${kernel_addr} ${ramdisk_addr} ${devicetree_addr}\0"\
*/
#endif /* __CONFIG_ZYNQ_GIGAZEE_H */
