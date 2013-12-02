//#include "w3150a.h"
#include "socket.h"
#include "netloading.h"
#include "delay.h"
#include "config.h"
#include "flash.h"
#include "serial.h"

uchar FLASH_BUF[256];

static void FlashPage(uint page, void *data, uint len)
{
	uint i;
	uint *wp = data;
	
	if(len > 256) len = 256;
	
	if(page >= 256)
	{
		if(page >= 480)
			return;
		RAMPZ = 1;
	}
	else RAMPZ = 0;

	page <<= 8;
	
	SpmCommand(page, (1 << PGERS) | (1 << SPMEN));
	SpmCommand(0, (1 << RWWSRE) | (1 << SPMEN));
	
	for(i = 0; i < len; i += 2, wp++)
		SpmBufferFill(i, *wp);

	for(; i < 256; i += 2)
		SpmBufferFill(i, 0xFFFF);
	
	SpmCommand(page, (1 << PGWRT) | (1 << SPMEN)); 
	SpmCommand(0, (1 << RWWSRE) | (1 << SPMEN));               
}

ulong swapl(ulong l)
{
	ulong ret=0;
	ret = (l & 0xFF) << 24;
	ret |= ((l >> 8) & 0xFF) << 16;
	ret |= ((l >> 16) & 0xFF) << 8;
	ret |= ((l >> 24) & 0xFF);
	return ret;
}

int loading(void) 
{
	uint size_recv;
	uint size_ttdiv256 = 0;
	uint size_ttdiv256remain = 0;
	ulong size_total;
	uint time_out, size_recvpp, page;
	uchar flag, last;

	size_total = 0;
	size_recvpp = 0;
	page = 0;
	flag = 0;
	last = 0;
	
	putStr((unsigned char*)"socket-");
	
	for(;flag==0;) flag = socket(SOCK_CONFIG, Sn_MR_TCP, REMOTE_UPDATE_PORT, 0);
	listen(SOCK_CONFIG);

	putStr((unsigned char *)"listen");
	
	time_out = 0;
	flag = 0;
	while (1) {
		if (getSn_SR(SOCK_CONFIG) == SOCK_ESTABLISHED) {
			if (flag == 0) {
				if (getSn_RX_RSR(SOCK_CONFIG) >= 4) {
					recv(SOCK_CONFIG, (uchar *)&size_total, 4);		// not in file
					size_total = swapl(size_total);
					size_ttdiv256 = size_total / 256;
					size_ttdiv256remain = size_total - (size_ttdiv256 * 256);
					flag = 1;
					/*
					putStr("\r\ntotal =");
					putData((uchar*)&size_total, 4);
					putStr("\r\nsize_ttdiv256 =");
					putData((uchar*)&size_ttdiv256, 2);
					putStr("\r\nsize_ttdiv256remain =");
					putData((uchar*)&size_ttdiv256remain, 2);
					putStr("\r\n");*/
				}
				time_out++;
				wait_10ms(1);
				if (time_out > 200) return(0);
			}
			else {
				if(size_ttdiv256) {
					if((size_recv = getSn_RX_RSR(SOCK_CONFIG)) >= 256) {
						putStr((unsigned char *)"*");
						recv(SOCK_CONFIG, FLASH_BUF, 256);
//						putData(FLASH_BUF, 256);
//						while(1);
						FlashPage(page++, FLASH_BUF, 256);
						size_recvpp += 256;
						size_ttdiv256--;
					}
				}
				else {
					if((size_recv = getSn_RX_RSR(SOCK_CONFIG)) >= size_ttdiv256remain) {
						putStr((unsigned char *)"-");
						recv(SOCK_CONFIG, FLASH_BUF, 256);//size_ttdiv256remain);
//						putData(FLASH_BUF, size_ttdiv256remain);
//						while(1);
						FlashPage(page, FLASH_BUF, size_ttdiv256remain);
						size_recvpp += size_ttdiv256remain;
						last++;
						break;
					}
				}
			} // if (flag == 0)
		} // if (state == SOCK_ESTABLISHED)
	}
	disconnect(SOCK_CONFIG);

	if((size_recvpp == size_total) && (last == 1)) return 1;
	else return 0;
}
