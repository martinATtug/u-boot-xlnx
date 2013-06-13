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

#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <asm/arch/mmc.h>
#include <asm/arch/nand.h>
#include <netdev.h>
#include <zynqpl.h>
#include <asm/arch/sys_proto.h>
#include <miiphy.h>

DECLARE_GLOBAL_DATA_PTR;

/* Bootmode setting values */
#define BOOT_MODES_MASK		0x0000000F
#define QSPI_MODE		0x00000001
#define NOR_FLASH_MODE		0x00000002
#define NAND_FLASH_MODE		0x00000004
#define SD_MODE			0x00000005
#define JTAG_MODE		0x00000000

#ifdef CONFIG_FPGA
Xilinx_desc fpga;

/* It can be done differently */
Xilinx_desc fpga010 = XILINX_XC7Z010_DESC(0x10);
Xilinx_desc fpga020 = XILINX_XC7Z020_DESC(0x20);
Xilinx_desc fpga030 = XILINX_XC7Z030_DESC(0x30);
Xilinx_desc fpga045 = XILINX_XC7Z045_DESC(0x45);
#endif

int board_init(void)
{
#ifdef CONFIG_FPGA
	u32 idcode;

	
	idcode = zynq_slcr_get_idcode();

	switch (idcode) {
	case XILINX_ZYNQ_7010:
		fpga = fpga010;
		break;
	case XILINX_ZYNQ_7020:
		fpga = fpga020;
		break;
	case XILINX_ZYNQ_7030:
		fpga = fpga030;
		break;
	case XILINX_ZYNQ_7045:
		fpga = fpga045;
		break;
	}
#endif

	/* temporary hack to clear pending irqs before Linux as it
	 * will hang Linux
	 */
	writel(0x26d, 0xe0001014);
	
	icache_enable();

#ifdef CONFIG_FPGA
	fpga_init();
	fpga_add(fpga_xilinx, &fpga);
#endif

	return 0;
}

char bin2char(unsigned char c)
{
	if((c >= 0) && (c <= 9)){
		return '0' + c;
	}
	return 'A' + c - 10;
}

int board_late_init(void)
{
//	const char	*devname;

	// MII patch enable MDIO interface
	*((uint *)0xE000B000) = 0x00000010;
	// set MDIO clock divider for cpu1x 160
	*((uint *)0xE000B004) = 0x00100000;


	switch ((zynq_slcr_get_boot_mode()) & BOOT_MODES_MASK) {
	case QSPI_MODE:
		setenv("modeboot", "qspiboot");
		break;
	case SD_MODE:
		setenv("modeboot", "sdboot");
		break;
	default:
		setenv("modeboot", "");
		break;
	}

	/* USB reset */
	/*mii write 1a 7 10; mii write 1a 7 0*/

/*
#if defined(CINFIG_MII_INIT)
	mii_init();
#endif
	devname = miiphy_get_current_dev();
	miiphy_write(devname, 0x1A, 0x07, 0x10);
	miiphy_write(devname, 0x1A, 0x07, 0x10);
	miiphy_write(devname, 0x1A, 0x07, 0x00);
	miiphy_write(devname, 0x1A, 0x07, 0x00);
*/
	return 0;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	unsigned char	i, temp_grade;
	unsigned char	mac[6];
	unsigned short	data;
	unsigned int	model;
	const char	*devname;
	char ethaddr[] = "00:0a:35:00:01:32";
	char eui48[] = "[00 0A 35 00 01 32]";
	char board[] = "TE0000-00-??F";
	char sc_ver[] = "0.00";

	u32 ret = 0;

#ifdef CONFIG_XILINX_AXIEMAC
	ret |= xilinx_axiemac_initialize(bis, XILINX_AXIEMAC_BASEADDR,
						XILINX_AXIDMA_BASEADDR);
#endif
#ifdef CONFIG_XILINX_EMACLITE
	u32 txpp = 0;
	u32 rxpp = 0;
# ifdef CONFIG_XILINX_EMACLITE_TX_PING_PONG
	txpp = 1;
# endif
# ifdef CONFIG_XILINX_EMACLITE_RX_PING_PONG
	rxpp = 1;
# endif
	ret |= xilinx_emaclite_initialize(bis, XILINX_EMACLITE_BASEADDR,
			txpp, rxpp);
#endif

#if defined(CONFIG_ZYNQ_GEM)
# if defined(CONFIG_ZYNQ_GEM_BASEADDR0)
	ret |= zynq_gem_initialize(bis, CONFIG_ZYNQ_GEM_BASEADDR0);
# endif
# if defined(CONFIG_ZYNQ_GEM_BASEADDR1)
	ret |= zynq_gem_initialize(bis, CONFIG_ZYNQ_GEM_BASEADDR1);
# endif
#endif
	/*Configure MAC address*/
	/*mii read 1a 9-b*/
#if defined(CINFIG_MII_INIT)
	mii_init();
#endif
	devname = miiphy_get_current_dev();
	miiphy_read(devname, 0x1A, 0x09, &data);
	mac[0] = (unsigned char)(data >> 8);
	mac[1] = (unsigned char)(data & 0xFF);
	miiphy_read(devname, 0x1A, 0x0A, &data);
	mac[2] = (unsigned char)(data >> 8);
	mac[3] = (unsigned char)(data & 0xFF);
	miiphy_read(devname, 0x1A, 0x0B, &data);
	mac[4] = (unsigned char)(data >> 8);
	mac[5] = (unsigned char)(data & 0xFF);
	
	for(i = 0; i < 6; i++){
		ethaddr[i*3 + 0] = bin2char(mac[i] >> 4);
		ethaddr[i*3 + 1] = bin2char(mac[i] & 0x0F);
		eui48[i*3 + 1] =  bin2char(mac[i] >> 4);
		eui48[i*3 + 2] =  bin2char(mac[i] & 0x0F);
	}
	setenv("ethaddr", ethaddr);
	setenv("eui48", eui48);
	/*Configure board information*/
	miiphy_read(devname, 0x1A, 0x02, &data);
	model = data << 6;
	miiphy_read(devname, 0x1A, 0x03, &data);
	model |= (data >> 10) & 0x3F;
	board[3] = '0' + ((model >> 12) & 0xF); //7
	board[4] = '0' + ((model >> 8) & 0xF);  //2
	board[5] = '0' + ((model >> 4) & 0xF);  //0
	board[8] = '0' + (model & 0xF);		//-01
	sc_ver[0] = '0' + (data & 0xF);		// SC ?.xx
	miiphy_read(devname, 0x1A, 0x04, &data);
	board[10] = '0' + ((data >> 14) & 0x3);	//Speed grade
	temp_grade = (data >> 12) & 0x3;
	switch(temp_grade){
		case 0: board[11] = 'C'; break;
		case 1: board[11] = 'E'; break;
		case 2: board[11] = 'I'; break;
	}
	setenv("board", board);
	sc_ver[2] = '0' + ((data >> 4) & 0xF);		// SC x.?x
	sc_ver[3] = '0' + (data & 0xF);			// SC x.x?
	setenv("scver", sc_ver);

	miiphy_write(devname, 0x1A, 0x07, 0x10);
	miiphy_write(devname, 0x1A, 0x07, 0x00);

	return ret;
}
#endif

#ifdef CONFIG_CMD_MMC
int board_mmc_init(bd_t *bd)
{
	// MMC Init run before SF init - we can put SF patch here
	if(((zynq_slcr_get_boot_mode()) & BOOT_MODES_MASK) == SD_MODE){
		// Little patch for SD mode
		*((uint *)0xE000D000) = 0x800AFCD7;
	}
	return zynq_mmc_init(bd);
}
#endif

#ifdef CONFIG_CMD_NAND
int board_nand_init(struct nand_chip *nand_chip)
{
	return zynq_nand_init(nand_chip);
}
#endif

int dram_init(void)
{
	gd->ram_size = CONFIG_SYS_SDRAM_SIZE;

	return 0;
}
