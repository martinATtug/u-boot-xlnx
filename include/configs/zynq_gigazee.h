/*
-- Copyright (C) 2013 Trenz Electronic GmbH
--
-- Permission is hereby granted, free of charge, to any person obtaining a 
-- copy of this software and associated documentation files (the "Software"), 
-- to deal in the Software without restriction, including without limitation 
-- the rights to use, copy, modify, merge, publish, distribute, sublicense, 
-- and/or sell copies of the Software, and to permit persons to whom the 
-- Software is furnished to do so, subject to the following conditions:
-- 
-- The above copyright notice and this permission notice shall be included 
-- in all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
-- OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
-- FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
-- IN THE SOFTWARE.
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

/* High Level Configuration Options */
#define CONFIG_ARMV7 /* CPU */
#define CONFIG_ZYNQ /* SoC */

/* Default environment */
#define CONFIG_IPADDR   	192.168.42.50
#define CONFIG_SERVERIP 	192.168.42.2

#define CONFIG_SYS_SDRAM_BASE	0
#define CONFIG_SYS_SDRAM_SIZE	PHYS_SDRAM_1_SIZE

/* Total Size of Environment Sector */
#define CONFIG_ENV_SIZE			(128 << 10)

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		0x400000

/* Serial drivers */
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 38400, 115200 }

/* Zynq serial driver */
#ifdef CONFIG_ZYNQ_SERIAL_UART0
# define CONFIG_ZYNQ_SERIAL_BASEADDR0	0xE0000000
# define CONFIG_ZYNQ_SERIAL_BAUDRATE0	CONFIG_BAUDRATE
# define CONFIG_ZYNQ_SERIAL_CLOCK0	50000000
#endif

#ifdef CONFIG_ZYNQ_SERIAL_UART1
# define CONFIG_ZYNQ_SERIAL_BASEADDR1	0xE0001000
# define CONFIG_ZYNQ_SERIAL_BAUDRATE1	CONFIG_BAUDRATE
# define CONFIG_ZYNQ_SERIAL_CLOCK1	50000000
#endif

#if defined(CONFIG_ZYNQ_SERIAL_UART0) || defined(CONFIG_ZYNQ_SERIAL_UART1)
#define CONFIG_ZYNQ_SERIAL
#endif

/* Ethernet driver */
#ifdef CONFIG_ZYNQ_GEM0
# define CONFIG_ZYNQ_GEM_BASEADDR0	0xE000B000
#endif

#ifdef CONFIG_ZYNQ_GEM1
# define CONFIG_ZYNQ_GEM_BASEADDR1	0xE000C000
#endif

#if defined(CONFIG_ZYNQ_GEM0) || defined(CONFIG_ZYNQ_GEM1)
# define CONFIG_NET_MULTI
# define CONFIG_ZYNQ_GEM
# define CONFIG_MII
# define CONFIG_SYS_FAULT_ECHO_LINK_DOWN
# define CONFIG_PHYLIB
# define CONFIG_PHY_MARVELL
# define CONFIG_SYS_ENET
#endif

/* SCU timer address is hardcoded */
#define CONFIG_SCUTIMER_BASEADDR	0xF8F00600
#ifndef CONFIG_CPU_FREQ_HZ
#define CONFIG_CPU_FREQ_HZ		800000000
#endif
#define CONFIG_SYS_HZ			1000

/* Miscellaneous configurable options */
#define CONFIG_SYS_PROMPT		"zynq-uboot> "
#define CONFIG_SYS_HUSH_PARSER	/* use "hush" command parser */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

#define CONFIG_CMDLINE_EDITING
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_LONGHELP
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)

/* Open Firmware flat tree */
#define CONFIG_OF_LIBFDT

#include <config_cmd_default.h>

#ifdef CONFIG_SYS_ENET
# define CONFIG_CMD_PING
# define CONFIG_CMD_MII
#else
# undef CONFIG_CMD_NET
# undef CONFIG_CMD_NFS
#endif

/* NOR */
#ifndef CONFIG_SYS_NO_FLASH
# define CONFIG_SYS_FLASH_BASE		0xE2000000
# define CONFIG_SYS_FLASH_SIZE		(16 * 1024 * 1024)
# define CONFIG_SYS_MAX_FLASH_BANKS	1
/* max number of sectors/blocks on one chip */
# define CONFIG_SYS_MAX_FLASH_SECT	512
# define CONFIG_SYS_FLASH_ERASE_TOUT	1000
# define CONFIG_SYS_FLASH_WRITE_TOUT	5000
# define CONFIG_FLASH_SHOW_PROGRESS	10
# define CONFIG_SYS_FLASH_CFI
# undef CONFIG_SYS_FLASH_EMPTY_INFO
# define CONFIG_FLASH_CFI_DRIVER
# undef CONFIG_SYS_FLASH_PROTECTION /* don't use hardware protection */
/* use buffered writes (20x faster) */
# define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#endif

/* QSPI */
#ifdef CONFIG_ZYNQ_SPI
# define CONFIG_SF_DEFAULT_SPEED	30000000
# define CONFIG_SPI_FLASH
# define CONFIG_SPI_FLASH_SPANSION
# define CONFIG_SPI_FLASH_STMICRO
# define CONFIG_SPI_FLASH_WINBOND
# define CONFIG_CMD_SPI
# define CONFIG_CMD_SF
#endif

/* MMC */
#ifdef CONFIG_MMC
# define CONFIG_GENERIC_MMC
# define CONFIG_SDHCI
# define CONFIG_ZYNQ_SDHCI
# define CONFIG_CMD_MMC
# define CONFIG_CMD_FAT
# define CONFIG_SUPPORT_VFAT
# define CONFIG_CMD_EXT2
# define CONFIG_DOS_PARTITION
#endif

/* NAND */
#ifdef CONFIG_NAND_ZYNQ
# define CONFIG_CMD_NAND
# define CONFIG_CMD_NAND_LOCK_UNLOCK
# define CONFIG_SYS_MAX_NAND_DEVICE 1
# define CONFIG_SYS_NAND_BASE XPSS_NAND_BASEADDR
# define CONFIG_SYS_NAND_ONFI_DETECTION
# define CONFIG_MTD_DEVICE
#endif

/* I2C */
#ifdef CONFIG_ZYNQ_I2C
# define CONFIG_CMD_I2C
# define CONFIG_HARD_I2C		1
# define CONFIG_SYS_I2C_SPEED		100000
# define CONFIG_SYS_I2C_SLAVE		1
# define CONFIG_ZYNQ_I2C_CTLR_1
#endif

/* EEPROM */
#ifdef CONFIG_ZYNQ_EEPROM
# define CONFIG_CMD_EEPROM
# define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
# define CONFIG_SYS_I2C_EEPROM_ADDR		0x54
# define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4
# define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	5
# define CONFIG_SYS_EEPROM_SIZE			1024 /* Bytes */
#endif

#ifndef CONFIG_ENV_IS_NOWHERE
# ifndef CONFIG_SYS_NO_FLASH
/* Environment in NOR flash */
#  define CONFIG_ENV_IS_IN_FLASH
# elif defined(CONFIG_ZYNQ_SPI)
/* Environment in Serial Flash */
#  define CONFIG_ENV_IS_IN_SPI_FLASH
# elif defined(CONFIG_NAND_ZYNQ)
/* Environment in NAND flash */
#  define CONFIG_ENV_IS_IN_NAND
# elif defined(CONFIG_SYS_NO_FLASH)
#  define CONFIG_ENV_IS_NOWHERE
# endif

# define CONFIG_ENV_SECT_SIZE		CONFIG_ENV_SIZE
# define CONFIG_ENV_OFFSET		0xF50000
# define CONFIG_CMD_SAVEENV	/* Command to save ENV to Flash */
#endif

/* For development/debugging */
#ifdef DEBUG
# define CONFIG_CMD_REGINFO
# define CONFIG_PANIC_HANG
#endif


/* default boot is according to the bootmode switch settings */
#define CONFIG_BOOTCOMMAND		"run $modeboot"
#define CONFIG_BOOTDELAY		3 /* -1 to Disable autoboot */
#define CONFIG_SYS_LOAD_ADDR		0 /* default? */

/* Keep L2 Cache Disabled */
#define CONFIG_SYS_L2CACHE_OFF
#define CONFIG_SYS_CACHELINE_SIZE	32

/* Physical Memory map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_1			0
#define CONFIG_SYS_TEXT_BASE		0x04000000

#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + \
					PHYS_SDRAM_1_SIZE - (16 * 1024 * 1024))

#define CONFIG_SYS_INIT_RAM_ADDR	0xFFFF0000
#define CONFIG_SYS_INIT_RAM_SIZE	0x1000
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + \
					CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)

/* Enable the PL to be downloaded */
#define CONFIG_FPGA
#define CONFIG_FPGA_XILINX
#define CONFIG_FPGA_ZYNQPL
#define CONFIG_CMD_FPGA

/* FIT support */
#define CONFIG_FIT		1
#define CONFIG_FIT_VERBOSE	1 /* enable fit_format_{error,warning}() */

#define CONFIG_CMD_BOOTZ
#undef CONFIG_BOOTM_NETBSD

/* FIXME this should be removed pretty soon */
#define XPSS_QSPI_BASEADDR		0xE000D000
#define XPSS_NAND_BASEADDR		0xE1000000
#define XPSS_CRTL_PARPORT_BASEADDR	0xE000E000
// For SD card in TE0701
#define SD_BASEADDR			0xE0100000
// For MMC onboard chip 
//#define SD_BASEADDR     		0xE0101000


#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS					\
	"bitstream_image=boot.bin\0"					\
	"bitstream_addr=0x1000000\0"					\
	"bitstream_size=0x450000\0"					\
	"bitstream_offset=0x000000\0"					\
	"kernel_image=uImage\0"						\
	"kernel_addr=0x3000000\0"					\
	"kernel_size=0x500000\0"					\
	"kernel_offset=0x450000\0" 					\
	"devicetree_image=devicetree.dtb\0"				\
	"devicetree_addr=0x2A00000\0"					\
	"devicetree_size=0x20000\0"					\
	"devicetree_offset=0x950000\0"					\
	"ramdisk_image=uramdisk.image.gz\0"				\
	"ramdisk_addr=0x2000000\0"					\
	"ramdisk_size=0x5E0000\0"					\
	"ramdisk_offset=0x970000\0" 					\
	"fdt_high=0x20000000\0"						\
	"initrd_high=0x20000000\0"					\
	"qspiboot=echo Trenz-Electronic ${board} SC ${scver} && "			\
		"echo Copying Linux from QSPI flash to RAM... && " 			\
		"sf probe 0 0 0 && " 							\
		"sf read ${kernel_addr} ${kernel_offset} ${kernel_size} && "		\
		"sf read ${devicetree_addr} ${devicetree_offset} ${devicetree_size} && "\
		"sf read ${ramdisk_addr} ${ramdisk_offset} ${ramdisk_size} && " 	\
		"fdt addr ${devicetree_addr} &&"				\
		"fdt set /amba/eth local-mac-address ${eui48} &&"		\
		"bootm  ${kernel_addr} ${ramdisk_addr} ${devicetree_addr}\0"	\
	"sdboot=echo Trenz-Electronic ${board}  ${scver} && "			\
		"echo Copying Linux from SD to RAM... && " 			\
		"mmcinfo && " 							\
		"fatload mmc 0 ${kernel_addr} ${kernel_image} && " 		\
		"fatload mmc 0 ${devicetree_addr} ${devicetree_image} && " 	\
		"fatload mmc 0 ${ramdisk_addr} ${ramdisk_image} && " 		\
		"fdt addr ${devicetree_addr} &&"				\
		"fdt set /amba/eth local-mac-address ${eui48} &&"		\
		"bootm ${kernel_addr} ${ramdisk_addr} ${devicetree_addr}\0" 	\
	"tftpfetch=echo TFTPing Linux to RAM... && " 				\
		"mw.b ${bitstream_addr} FF ${bitstream_size} &&" 		\
		"tftp ${bitstream_addr} ${bitstream_image} && " 	\
		"mw.b ${kernel_addr} FF ${kernel_size} &&" 			\
		"tftp ${kernel_addr} ${kernel_image} && " 			\
		"mw.b ${devicetree_addr} FF ${devicetree_size} &&" 		\
		"tftp ${devicetree_addr} ${devicetree_image} && " 		\
		"mw.b ${ramdisk_addr} FF ${ramdisk_size} &&"	 		\
		"tftp ${ramdisk_addr} ${ramdisk_image} && " 			\
		"fdt addr ${devicetree_addr} &&"				\
		"fdt set /amba/eth local-mac-address ${eui48}\0"		\
	"sdfetch=echo Read files from SD... && " 				\
		"mmcinfo && " 							\
		"mw.b ${bitstream_addr} FF ${bitstream_size} &&" 		\
		"fatload mmc 0 ${bitstream_addr} ${bitstream_image} && " 	\
		"mw.b ${kernel_addr} FF ${kernel_size} &&" 			\
		"fatload mmc 0 ${kernel_addr} ${kernel_image} && " 		\
		"mw.b ${devicetree_addr} FF ${devicetree_size} &&" 		\
		"fatload mmc 0 ${devicetree_addr} ${devicetree_image} && " 	\
		"mw.b ${ramdisk_addr} FF ${ramdisk_size} &&"	 		\
		"fatload mmc 0 ${ramdisk_addr} ${ramdisk_image} && " 		\
		"fdt addr ${devicetree_addr} &&"				\
		"fdt set /amba/eth local-mac-address ${eui48}\0"		\
	"reflash_all=echo Full reflash from Memory... && " 					\
		"sf probe 0 0 0 && " 								\
		"sf update ${bitstream_addr} ${bitstream_offset} ${bitstream_size} && " 	\
		"sf update ${kernel_addr} ${kernel_offset} ${kernel_size} && " 			\
		"sf update ${devicetree_addr} ${devicetree_offset} ${devicetree_size} && "	\
		"sf update ${ramdisk_addr} ${ramdisk_offset} ${ramdisk_size}\0" 		\
	"reflash_linux=echo Reflash linux from Memory... && " 					\
		"sf probe 0 0 0 && " 								\
		"sf update ${kernel_addr} ${kernel_offset} ${kernel_size} && " 			\
		"sf update ${devicetree_addr} ${devicetree_offset} ${devicetree_size} && "	\
		"sf update ${ramdisk_addr} ${ramdisk_offset} ${ramdisk_size}\0" 		\
	"reflash_dt=echo Reflash Device Tree from Memory... && " 				\
		"sf probe 0 0 0 && " 								\
		"sf update ${devicetree_addr} ${devicetree_offset} ${devicetree_size}\0"	\
	"linux=bootm  ${kernel_addr} ${ramdisk_addr} ${devicetree_addr}\0"	\
	"linaro=bootm  ${kernel_addr} - ${devicetree_addr}\0"			\
	"tftpboot=echo TFTPing Linux to RAM... && " 				\
		"tftp ${kernel_addr} ${kernel_image} && " 			\
		"tftp ${devicetree_addr} ${devicetree_image} && " 		\
		"tftp ${ramdisk_addr} ${ramdisk_image} && " 			\
		"fdt addr ${devicetree_addr} &&"				\
		"fdt set /amba/eth local-mac-address ${eui48} &&"		\
		"bootm  ${kernel_addr} ${ramdisk_addr} ${devicetree_addr}\0"	\
	"updatemac=fdt addr ${devicetree_addr} && "\
		"fdt set /amba/eth local-mac-address \"${eui48}\"\0"
#endif /* __CONFIG_ZYNQ_GIGAZEE_H */
