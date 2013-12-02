#include <avr/io.h>

#include "types.h"
#include "delay.h"

#include "socket.h"
#include "config.h"
#include "netloading.h"
#include "iinchip_conf.h"
#include "serial.h"
#include "socket.h"

#include <avr/eeprom.h>

extern uchar FLASH_BUF[256];

IGM_INFO ConfigMsg;

void init_board(void)
{
	EICRA=0x00;
	EICRB=0x00;
	EIMSK=0x00;
	EIFR=0x00;

	MCUCR |= (1 << SRE);
	XMCRA = (1 << SRL2) | (1 << SRW00) | (1 << SRW11);

	// Low sector   : 0x1100 ~ 0x7FFF	1 wait-state
	// Upper sector : 0x8000 ~ 0xFFFF	2 wait-state

}

#define EEPOP				0
typedef struct
{
	unsigned char op[4];
	unsigned char ver[2];
	unsigned char mac[6];
	unsigned char ip[4];
	unsigned char subnet[4];
	unsigned char gw[4];
} StrConfigParam;

StrConfigParam NetworkParam;
void initNet(void)
{
	unsigned char tx_mem_conf[8] = {8,8,8,8,8,8,8,8};  
//	unsigned char buf[10] = " ";
	
	//W5300 Chip Init
	iinchip_init();
	

	eeprom_read_block(&NetworkParam, (unsigned char*)EEPOP, sizeof(NetworkParam));
	setSHAR(NetworkParam.mac);
	setGAR(NetworkParam.gw);
	setSUBR(NetworkParam.subnet);
	setSIPR(NetworkParam.ip);

#ifdef __DEF_IINCHIP_INT__
	setIMR(0xEF);
#endif
	
	//sysinit(MY_NET_MEMALLOC, MY_NET_MEMALLOC);

   /* allocate internal TX/RX Memory of W5300 */
   if(!sysinit(tx_mem_conf, tx_mem_conf))           
   {
      while(1);
   }
}

int main(void)
{
	init_board();
	initUart();
	putStr((unsigned char *)"WIZ-Embedded WebServer\r\nBoot Start\r\n");	
	
	initNet();
	
	if(loading()==1) {
		// GOOD

		putStr((unsigned char *)"Write ok\r\n");		

		((void (*)())0x0000)();		
		
		GoApp();
	}
	else {
		// ERROR @_@
		putStr((unsigned char *)"Write fail\r\n");			
		while(1);

	}
	return 0;
}
