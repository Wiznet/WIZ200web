 /*
 * (c)COPYRIGHT
 * ALL RIGHT RESERVED
 *
 * FileName : main.c
 * Brief : source codes for WIZ-Embedded WebServer A.K
 * This code is optimized at AVR-GCC 4.3.3(20090313).
 */
#include <stdio.h> 
#include <string.h>
#include "../../mcu/types.h"
#include "../../mcu/delay.h"
#include "../../mcu/serial.h"
#include "../../evb/lcd.h"
#include "../../evb/evb.h"

#include "../../iinchip/socket.h"

#include "../../evb/romfile.h"
#include "../../evb/tc77.h"
#include "../../inet/httpd.h"
#include "task_config.h"
#include "dhcp_task.h"
#include "../../evb/config.h"
#include "../../util/sockutil.h"
//-----------------------------------------------------------------------------

//#define  WEB_DEBUG

#define MY_NET_MAC			{0x00, 0x08, 0xdc, 0x00, 0x00, 0x00}	// MY Mac Address : 00.08.DC.00.00.00

#define MY_NET_GWIP			{192,  168, 0,  1}	// MY Gateway IP    : 192.168.0.1
#define MY_DESTINATIONIP	{192,  168, 0,  2}	// MY Destination   : 192.168.0.2
#define MY_SOURCEIP			{192,  168, 1,  3}	// MY Source IP     : 192.168.0.3
#define MY_SUBNET			{255, 255, 255,   0}

#define MY_NET_MEMALLOC		0x55					// MY iinchip memory allocation

#define MY_LISTEN_PORT		5000					// MY Listen Port  : 5000 
#define MY_CONNECT_PORT		3000					// MY Connect Port : 3000

#define SOCK_TCPC			0
#define SOCK_TCPS			1


#define DEFAULT_HTTP_PORT			80
//-----------------------------------------------------------------------------

#define EVB_NET_SIP	"$SRC_IP_ADDRES$"
#define EVB_NET_GWIP	"$GW_IP_ADDRESS$"
#define EVB_NET_SN	"$SUB_NET__MASK$"
#define EVB_NET_DNS	"$DNS_SERVER_IP$"
#define EVB_NET_MAC	"$SRC_MAC_ADDRESS$"

#define EVB_LCD_TEXT 	"$LCD_TEXT_VALUE$"
#define EVB_LED0_IMG	"$LED0_IMG$"
#define EVB_LED1_IMG	"$LED1_IMG$"
#define EVB_LED2_IMG	"$LED2_IMG$"
#define EVB_LED3_IMG	"$LED3_IMG$"
#define EVB_LED0_STAT	"$LED_0$"
#define EVB_LED1_STAT	"$LED_1$"
#define EVB_LED2_STAT	"$LED_2$"
#define EVB_LED3_STAT	"$LED_3$"


void evb_lcd_logo(void);
void RomFileTest(void);
void ProcessWebSever(u_char ch);
static u_int replace_sys_env_value(u_char* base, u_int len);

static u_char* http_response;		/**< Pointer to HTTP response */
static st_http_request *http_request;	/**< Pointer to HTTP request */
extern StrConfigParam NetworkParam, MSGConfig;

unsigned char bchannel_start;

unsigned char m_FlagWrite = 0;
unsigned char m_FlagFlashWrite = 0;

unsigned long m_FileSize = 0;
unsigned long m_FileWriteCount = 0;

//  
//-----------------------------------------------------------------------------
void NetInit(void)
{
	volatile unsigned long dd = 100000;
  /* 
	unsigned char mac[6]	= MY_NET_MAC;
	unsigned char sm[4]	= MY_SUBNET;
	unsigned char gwip[4]	= MY_NET_GWIP;
	unsigned char m_sip[4]	= MY_SOURCEIP;
*/
	unsigned char tx_mem_conf[8] = {8,8,8,8,8,8,8,8};          // for setting TMSR regsiter
//	unsigned char rx_mem_conf[8] = {8,8,8,8,8,8,8,8};          // for setting RMSR regsiter
	
	//W5300 Chip Init
	iinchip_init();

	while(dd--);
	/*
	//Set MAC Address
	setSHAR(mac);

	//Set Gateway
	setGAR(gwip);

	//Set Subnet Mask
	setSUBR(sm);

	//Set My IP
	setSIPR(m_sip);*/
	

#ifdef __DEF_IINCHIP_INT__
	setIMR(0xEF);
#endif
	
	//sysinit(MY_NET_MEMALLOC, MY_NET_MEMALLOC);

   /* allocate internal TX/RX Memory of W5300 */
   if(!sysinit(tx_mem_conf, tx_mem_conf))           
   {
  //    printf("MEMORY CONFIG ERR.\r\n");
      while(1);
   }	
}
//-----------------------------------------------------------------------------


void DisplayBar(void)
{
	printf("\r\n================================================\r\n");
}

void DisplayConfig(void)
{

	u_char i = 0;
	DisplayBar();
	printf("       Net Config Information..\r\n");
	DisplayBar();
	
	printf("MAC ADDRESS      : ");
	//for(i=0; i<6;i++)printf("0x%02X.",IINCHIP_READ(SHAR0+i));
	printf("%02X:%02X:%02X:%02X:%02X:%02X",IINCHIP_READ(SHAR0+0),IINCHIP_READ(SHAR0+1),IINCHIP_READ(SHAR0+2),IINCHIP_READ(SHAR0+3),IINCHIP_READ(SHAR0+4),IINCHIP_READ(SHAR0+5));
	

	printf("\r\nSUBNET MASK      : ");
	for(i=0; i < 4; i++)
	{
		printf("%d.", (char)IINCHIP_READ(SUBR0+i));
	}


	printf("\r\nG/W IP ADDRESS   : ");
	for(i=0; i < 4; i++)
	{
		printf("%d.", (char)IINCHIP_READ(GAR0+i));
	}

	printf("\r\nLOCAL IP ADDRESS : ");
	for(i=0; i < 4; i++)
	{
		printf("%d.", (char)IINCHIP_READ(SIPR0+i));
	}

	DisplayBar();
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void FlashWrite(unsigned char *pRcvBuffer, unsigned int len)
{
	unsigned int i;

	for(i=0;i<len;i++)
	{
		if(m_FlagFlashWrite)
		{

			if(m_FileWriteCount==3)
			{
				memcpy((unsigned char *)&m_FileSize, &pRcvBuffer[0], 4);
			}
			else if(m_FileWriteCount>3)		
			{
				//File Write
				write_to_flash(pRcvBuffer[i]);
			}

			m_FileWriteCount++;	

			if(m_FileWriteCount==(m_FileSize+4))
			{
				//end file send
				
				write_end_page();
				m_FlagFlashWrite =0;
				
				disconnect(0);
				
				((void (*)())0x0000)();		// reset
				return;
			}
		}
		else
		{
		}
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void ProcessRomfileUpdate(unsigned char Sock)
{
	#define MAX_BUF_SIZE	1460
	unsigned int len;							

	volatile uint8 *data_buf = (volatile unsigned char*)(RX_BUF+TX_RX_MAX_BUF_SIZE);
	uint16 port = CONFIG_UP_PORT;
	
	switch(getSockStatus(Sock))
	{
	case SOCK_ESTABLISHED:
		//check Rx data
		if((len = getRecvSize(Sock)) > 0) 			
		{
			//if Rx data size is lager than TX_RX_MAX_BUF_SIZE 
			if (len > MAX_BUF_SIZE) len = MAX_BUF_SIZE;	
			
			//read the received data
			len = recv(Sock, (uint8*)data_buf, len);

			FlashWrite((uint8*)data_buf, len);
		}		
		break;
		
	case SOCK_CLOSE_WAIT:                           		
		//If the client request to close
		disconnect(Sock);
		break;
		
   case SOCK_CLOSED:                   // CLOSED
		close(Sock);                        // close the SOCKET
		socket(Sock, Sn_MR_TCP, port,0);   // open the SOCKET  
		break;
		
   case SOCK_INIT:                     // The SOCKET opened with TCP mode
		//connect(Sock, m_ConfigServerIp, port);
		listen(Sock);
		//printf("%d : TCP Server(%d) Started.\r\n", Sock, port);
		break;		
	}
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
int main(void)
{
	//EVB Initialize
	evb_init();
	
	printf("\r\nWIZ-Embedded WebServer Test Program.");

	
	//W5300 Chip Initialize
	//----------------------------
	NetInit();
	
	SetConfig();
	//----------------------------

	dhcp_task_init();
	
	evb_lcd_logo();
	
	//Display Net Configuration..
	DisplayConfig();	
	
	InitRomFile();

	
	RomFileTest();
	
	tc77_init();	

	while (1)
	{
		ProcessRomfileUpdate(0);		
		ProcessConfig(1);
		if(NetworkParam.dhcp)
		{
			dhcp_task();
		}

		ProcessWebSever(3);
		ProcessWebSever(4);
		ProcessWebSever(5);
		ProcessWebSever(6);
		ProcessWebSever(7);	
	}		
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void evb_lcd_logo(void)
{
	unsigned long sip;
	
	memcpy((unsigned char*)&sip, &NetworkParam.ip[0], 4);
	evb_set_lcd_text(1,(u_char*)inet_ntoa_pad(ntohl(sip)));
}

void RomFileTest(void)
{
	unsigned int address = 0;
	unsigned int len = 0;
	unsigned char ret;
	
	printf("index.html file search: ");	
	ret = search_file_rom((unsigned char *)"index.html", (unsigned long *)&address, (unsigned long *)&len);

	if(ret>0)printf("OK.\r\n");
	else printf("Fail!\r\n");
}
//-----------------------------------------------------------------------------



void cgi_ipconfig(void)
{
	u_char * param;

	if((param = get_http_param_value(http_request->URI,"sip")))
	{
		inet_addr_((u_char*)param, &NetworkParam.ip[0]);		
	}
	if((param = get_http_param_value(http_request->URI,"gwip")))
	{
		inet_addr_((u_char*)param, &NetworkParam.gw[0]);	
	}			
	if((param = get_http_param_value(http_request->URI,"sn")))
	{
		inet_addr_((u_char*)param, &NetworkParam.subnet[0]);		
	}
	if((param = get_http_param_value(http_request->URI,"dns")))
	{
		//NetConf.dns= htonl(inet_addr((u_char*)param));
	}

	eeprom_write_block(&NetworkParam, (unsigned char*)EEPOP, sizeof(NetworkParam));
	eeprom_write_byte((unsigned char*)EEPADDR_VER, VER_H);
	eeprom_write_byte((unsigned char*)(EEPADDR_VER+1), VER_L);				
}


/**
 @brief	Analyse HTTP request and then services WEB.
*/
extern unsigned int m_OldPage;
static void proc_http(SOCKET s,	u_char * buf, int length)
{
	char* name;
	char * param;
	unsigned long file_len;
	unsigned int send_len;
	unsigned long content = 0;

	http_response = (u_char*)RX_BUF;
	http_request = (st_http_request*)TX_BUF;
	
	parse_http_request(http_request, buf);			// After analyze request, convert into http_request

	//method Analyze
	switch (http_request->METHOD)				
	{
	case METHOD_ERR :	
		memcpy_P(http_response, ERROR_REQUEST_PAGE, sizeof(ERROR_REQUEST_PAGE));
		send(s, (u_char *)http_response, strlen((char*)http_response));
		break;
	case METHOD_HEAD:
	case METHOD_GET :
	case METHOD_POST :
		name = get_http_uri_name(http_request->URI);
		
		if (!strcmp(name, "/")) strcpy(name,"index.html");	// If URI is "/", respond by index.htm 
		find_http_uri_type(&http_request->TYPE, name);	//Check file type (HTML, TEXT, GIF, JPEG are included)


#ifdef WEB_DEBUG
		// denug 
		printf("\r\nreq_type = %d, name = %s", http_request->TYPE, name);
#endif


		if(http_request->TYPE == PTYPE_CGI)
		{
			if(strstr(name,"LCDCTL.CGI"))
			{
				if((param = get_http_param_value(http_request->URI,"lcd0")))
				{
					*(param+16) = 0;
					evb_set_lcd_text(1,(u_char*)param);
				}
				
				strcpy(name,"dout.htm");
				find_http_uri_type(&http_request->TYPE, name);				
			}
			else if(strstr(name,"LEDCTL.CGI"))
			{			
				if((param = get_http_param_value(http_request->URI,"led0")))
				{
					if(!strcmp(param,"on")) led_on(0);
					else			led_off(0);
				}
				else led_off(0);
				
				if((param = get_http_param_value(http_request->URI,"led1")))
				{
					if(!strcmp(param,"on"))led_on(1);
					else led_off(1);
				}
				else led_off(1);
				
				if((param = get_http_param_value(http_request->URI,"led2")))
				{
					if(!strcmp(param,"on"))led_on(2);
					else led_off(2);
				}
				else led_off(2);
				
				if((param = get_http_param_value(http_request->URI,"led3")))
				{
					if(!strcmp(param,"on"))led_on(3);
					else led_off(3);
				}
				else led_off(3);
				
				strcpy(name,"dout.htm");
				find_http_uri_type(&http_request->TYPE, name);
			}
			else if(strstr(name,"NETCONFIG.CGI"))
			{
				cgi_ipconfig();

				memcpy_P(http_response, RETURN_CGI_PAGE, sizeof(RETURN_CGI_PAGE));
				send(s, (u_char *)http_response, strlen((char*)http_response));				
				
				disconnect(0);
				
				((void (*)())0x0000)();		// reset
				
				return;
			}
		}

		
		/* Search the specified file in stored binaray html image */
		//if (!search_file(name, &content, &file_len))		//if the file do not exist then
		if(!search_file_rom((unsigned char *)name, &content, &file_len))
		{
			memcpy_P(http_response, ERROR_HTML_PAGE, sizeof(ERROR_HTML_PAGE));
			send(s, (u_char *)http_response, strlen((char*)http_response));	
#ifdef WEB_DEBUG				
			printf("\r\nUnknown Page");
#endif				
		} 
		else	// if search file sucess 
		{
#ifdef WEB_DEBUG				
			printf("\r\nfind file [%s] ok", name);
#endif				

			if(http_request->TYPE != PTYPE_CGI)			
			{
				make_http_response_head((char*)http_response, http_request->TYPE, (u_long)file_len);			
				send(s, http_response, strlen((char*)http_response));
				
#ifdef WEB_DEBUG				
			printf("\r\n [%d]send header\r\n", http_request->TYPE);
			printf("%s", http_response);
#endif				
			}
			
			
			while(file_len) 
			{
				if (file_len >= TX_RX_MAX_BUF_SIZE-1)
					send_len = TX_RX_MAX_BUF_SIZE-1;
				else	send_len = file_len;
			
				read_from_flashbuf(content, &http_response[0], send_len);
				
				*(http_response+send_len+1) = 0;

				// Replace htmls' system environment value to real value
				if ((http_request->TYPE==PTYPE_HTML) || (http_request->TYPE==PTYPE_CGI) || (http_request->TYPE==PTYPE_XML))
				{
						send_len = replace_sys_env_value(http_response,send_len);
				}

				send(s, http_response, send_len);
				content += send_len;
				file_len -= send_len;
			}
        }
		break;
	default :
		break;
	}
}



/**
 @brief	Replace HTML's variables to system configuration value
*/
static u_int replace_sys_env_value(u_char* base, u_int len)
{
	u_char str[18]={0x00,};	
	u_char *ptr,*tptr;
	tptr = ptr = base;
	unsigned int read_val = 0;
	u_char i, str_len;

	
	while((ptr=(u_char*)strchr((char*)tptr,'$')))
	{
		if((tptr=(u_char*)strstr((char*)ptr,EVB_NET_SIP)))
		{
			sprintf((char*)str,"%d.%d.%d.%d",NetworkParam.ip[0],NetworkParam.ip[1], NetworkParam.ip[2], NetworkParam.ip[3]);
			str_len = strlen(str);
			for (i = str_len; i < 15; i++) str[i] = 0x20; // replace null to space
			memcpy(tptr, str, strlen(str));
			tptr += strlen(str);
			
		}
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_NET_GWIP)))
		{
			sprintf((char*)str,"%d.%d.%d.%d",NetworkParam.gw[0],NetworkParam.gw[1], NetworkParam.gw[2], NetworkParam.gw[3]);
			str_len = strlen(str);
			for (i = str_len; i < 15; i++) str[i] = 0x20; // replace null to space
			memcpy(tptr, str, strlen(str));
			tptr += strlen(str);
			
		}
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_NET_SN)))
		{
			sprintf((char*)str,"%d.%d.%d.%d",NetworkParam.subnet[0],NetworkParam.subnet[1], NetworkParam.subnet[2], NetworkParam.subnet[3]);
			str_len = strlen(str);
			for (i = str_len; i < 15; i++) str[i] = 0x20; // replace null to space
			memcpy(tptr, str, strlen(str));
			tptr += strlen(str);
		}

		// suould be removed : not match to html
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_NET_DNS)))
		{
			sprintf((char*)str,"%d.%d.%d.%d",NetworkParam.ip[0],NetworkParam.ip[1], NetworkParam.ip[2], NetworkParam.ip[3]);
			str_len = strlen(str);
			for (i = str_len; i < 15; i++) str[i] = 0x20; // replace null to space
			memcpy(tptr, str, strlen(str));
			tptr += strlen(str);
		}
		
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_NET_MAC)))
		{
			sprintf((char*)str,"%02X:%02X.",NetworkParam.mac[0],NetworkParam.mac[1]);
			sprintf((char*)(str+6),"%02X:%02X:",NetworkParam.mac[2],NetworkParam.mac[3]);
			sprintf((char*)(str+12),"%02X:%02X",NetworkParam.mac[4],NetworkParam.mac[5]);
			memcpy(tptr,str,17);
			tptr+=17;
		}
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LCD_TEXT)))
		{
			memset(tptr,0x20,16);
			memcpy(tptr,(unsigned char*)evb_get_lcd_text(1),16);
			tptr+=16;
		}		
		//-------------------------------------------------------		
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LED0_IMG)))
		{
			memset(tptr,0,10);
			
			if(led_state(0)==LED_ON)memcpy(tptr,"led_on.gif",10);
			else memcpy(tptr,"led_of.gif",10);

			tptr+=10;
		}
		//-------------------------------------------------------
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LED1_IMG)))
		{
			memset(tptr,0,10);
			if(led_state(1)==LED_ON)memcpy(tptr,"led_on.gif",10);
			else memcpy(tptr,"led_of.gif",10);

			tptr+=10;
		}
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LED2_IMG)))
		{
			memset(tptr,0,10);
			if(led_state(2)==LED_ON) memcpy(tptr,"led_on.gif",10);
			else			 memcpy(tptr,"led_of.gif",10);
			tptr+=10;
		}
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LED3_IMG)))
		{
			memset(tptr,0,10);
			if(led_state(3)==LED_ON) memcpy(tptr,"led_on.gif",10);
			else			 memcpy(tptr,"led_of.gif",10);
			tptr+=10;
		}		
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LED0_STAT)))
		{
			memset(tptr,0x20,7);
			if(led_state(0)==LED_ON) memcpy(tptr,"checked",7);
			tptr+=7;
		}			
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LED1_STAT)))
		{
			memset(tptr,0x20,7);
			if(led_state(1)==LED_ON) memcpy(tptr,"checked",7);
			tptr+=7;
		}
		//-------------------------------------------------------
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LED2_STAT)))
		{
			memset(tptr,0x20,7);
			if(led_state(2)==LED_ON) memcpy(tptr,"checked",7);
			tptr+=7;
		}
		//-------------------------------------------------------
		else if((tptr=(u_char*)strstr((char*)ptr,EVB_LED3_STAT)))
		{
			memset(tptr,0x20,7);
			if(led_state(3)==LED_ON) memcpy(tptr,"checked",7);
			tptr+=7;
		}
		//-------------------------------------------------------
		//Switch input
		else if((tptr=(u_char*)strstr((char*)ptr,"$SW_VAL1$")))
		{
			memset(tptr,0,9);
			if(sw_state(0)) memcpy(tptr,"sw_on.gif",9);
			else			 memcpy(tptr,"sw_of.gif",9);
			tptr+=9;			
		}
		else if((tptr=(u_char*)strstr((char*)ptr,"$SW_VAL2$")))
		{
			memset(tptr,0,9);
			if(sw_state(1)) memcpy(tptr,"sw_on.gif",9);
			else			 memcpy(tptr,"sw_of.gif",9);
			tptr+=9;	
		}
		//-------------------------------------------------------			
		//Temperature Input
		else if((tptr=(u_char*)strstr((char*)ptr,"$T_V1$")))
		{
			memset(tptr,0,6);
			
			if(tc77_read(&read_val))
			{
				
			}
			else
			{
				read_val = read_val-16;
				read_val = (unsigned int)((float)read_val*0.625);
				
				sprintf((char*)str, "%5d%%", 10+read_val/8);	
			}

			memcpy(tptr,str,6);
			tptr+=7;
		}
		else if((tptr=(u_char*)strstr((char*)ptr,"$T_V2$")))
		{
			memset(tptr,0,6);
			
			if(tc77_read(&read_val))
			{
				read_val = (unsigned int)((float)(4096-read_val)*0.625);
				
				sprintf((char*)str, "-%3d.%2d", read_val/10, read_val%10);	
			}
			else
			{
				read_val = read_val-16;
				read_val = (unsigned int)((float)read_val*0.625);

				sprintf((char*)str, "%3d.%2d", read_val/10, read_val%10);	
			}
			
			memcpy(tptr,str,6);
			tptr+=7;
		}

		//ADC VR Input	
		else if((tptr=(u_char*)strstr((char*)ptr,"$AD_V2$")))
		{
			read_val = (1024-AdcRead(0));

			memset(tptr,0x20, 13);
			sprintf((char*)str, "%d</adc>", read_val);	
			str_len = strlen(str);
			memcpy(tptr,str,str_len);
			tptr+=str_len;
		}
		//-------------------------------------------------------	
		else
		{
			return len;
			
			if(ptr==base)
			{
				return len;
			}
			tptr = ptr;
			break;
		}
	}

	if(!ptr) return len;
	
	return (u_int)(tptr-base);
}


//processing http protocol , and excuting the followed fuction.
void ProcessWebSever(u_char ch)
{
	int len;
	u_int wait_send=0;

	http_request = (st_http_request*)RX_BUF;		// struct of http request
	
	/* http service start */
	switch(getSn_SR(ch))
	{
	case SOCK_ESTABLISHED:
		if(bchannel_start==1)
		{
			bchannel_start = 2;
		}
		if ((len = getSn_RX_RSR(ch)) > 0)		
		{
			if ((u_int)len > MAX_URI_SIZE) len = MAX_URI_SIZE;				
			len = recv(ch, (u_char*)http_request, len);
			*(((u_char*)http_request)+len) = 0;
			
#ifdef WEB_DEBUG		
			printf( "\r\n\r\nHTTP REQUEST -");
#endif				
			proc_http(ch, (u_char*)http_request, len);	// request is processed
		
			while(getSn_TX_FSR(ch)!= getIINCHIP_TxMAX(ch))
			{
			
				if(wait_send++ > 1500)
				{
#ifdef WEB_DEBUG_				
					printf( "HTTP Response send fail");
#endif				
					break;
				}
				//Delay(1);
				
			}
			disconnect(ch);
		}
		break;


	case SOCK_CLOSE_WAIT:   
#ifdef WEB_DEBUG	
		printf("CLOSE_WAIT : %d",ch);	// if a peer requests to close the current connection
#endif		
		disconnect(ch);
		bchannel_start = 0;
	case SOCK_CLOSED:                   
		if(!bchannel_start)
		{
#ifdef WEB_DEBUG		
			//printf("%d : Web Server Started.\r\n",ch);
			printf("\r\nClose & Web Server Started.\r\n");
#endif				
			bchannel_start = 1;
		}

		if(socket(ch, Sn_MR_TCP, DEFAULT_HTTP_PORT, 0x00) == 0)    /* reinitialize the socket */
		//DEFAULT_LISTEN_PORT
		{
			bchannel_start = 0;
		}
		else	listen(ch);
		break;
	}	// end of switch 
}


