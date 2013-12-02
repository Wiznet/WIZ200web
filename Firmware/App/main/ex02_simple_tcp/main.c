 /*
 * (c)COPYRIGHT
 * ALL RIGHT RESERVED
 *
 * FileName : main.c
 * Brief : source codes for WIZ-Embedded WebServer A.K
 * This code is optimized at AVR-GCC 4.2.2(20071221).
 
 * Revision History :
 * ----------	-------		------------------------------------------------
 * 	Date			version	  	Description
 * ----------	-------  	------------------------------------------------
 * 03/28/2007	1.0.0.0		Release version
 * ----------	-------		------------------------------------------------
 * 01/08/2008	1.1.0.0		Check if W5100 register and EEPROM are the same value 
 *											before displaying network information.
 							Changed W5100 Driver(v1.2).
 							Removed WinAVR-20050214 codes(UART).
 							Changed check_leaseIP() function in DHCP.C.
 * ----------	-------		------------------------------------------------
 */
 
#include <string.h>
#include "../../mcu/types.h"
#include "../../mcu/delay.h"
#include "../../mcu/serial.h"
#include "../../evb/lcd.h"
#include "../../evb/evb.h"
#include "../../iinchip/socket.h"


//-----------------------------------------------------------------------------

//#define  WEB_DEBUG

#define MY_NET_MAC			{0x00, 0x08, 0xdc, 0x00, 0x00, 0x00}	// MY Mac Address : 00.08.DC.00.00.00

#define MY_NET_GWIP			{192,  168, 0,  1}	// MY Gateway IP    : 192.168.0.1
#define MY_DESTINATIONIP	{192,  168, 0,  2}	// MY Destination   : 192.168.0.2
#define MY_SOURCEIP			{192,  168, 0,  3}	// MY Source IP     : 192.168.0.3
#define MY_SUBNET			{255, 255, 255,   0}

#define MY_NET_MEMALLOC		0x55					// MY iinchip memory allocation

#define MY_LISTEN_PORT		5000					// MY Listen Port  : 5000 
#define MY_CONNECT_PORT		3000					// MY Connect Port : 3000

#define TX_RX_MAX_BUF_SIZE	1460
#define SOCK_TCPC			0
#define SOCK_TCPS			1



#define DEFAULT_HTTP_PORT			80
//-----------------------------------------------------------------------------

void ProcessTCPServer(SOCKET Sock, unsigned int Port);
void ProcessUDP(SOCKET Sock, unsigned int Port);

//-----------------------------------------------------------------------------
void NetInit(void)
{
	unsigned long dd = 100000;

	unsigned char mac[6]	= MY_NET_MAC;
	unsigned char sm[4]	= MY_SUBNET;
	unsigned char gwip[4]	= MY_NET_GWIP;
	unsigned char m_sip[4]	= MY_SOURCEIP;

	unsigned char tx_mem_conf[8] = {8,8,8,8,8,8,8,8};          // for setting TMSR regsiter
//	unsigned char rx_mem_conf[8] = {8,8,8,8,8,8,8,8};          // for setting RMSR regsiter
	
	//W5300 Chip Init
	iinchip_init();

	while(dd--);

	//Set MAC Address
	setSHAR(mac);

	//Set Gateway
	setGAR(gwip);

	//Set Subnet Mask
	setSUBR(sm);

	//Set My IP
	setSIPR(m_sip);
	

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
	for(i=0; i<6;i++)printf("0x%02X.",IINCHIP_READ(SHAR0+i));
	

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
int main(void)
{
	//EVB Initialize
	evb_init();
	
	printf("\r\nWIZ-Embedded WebServer - Simple TCP, UDP Test Program.");

	
	//W5300 Chip Initialize
	//----------------------------
	NetInit();
	

	//----------------------------


	//Display Net Configuration..
	DisplayConfig();	
	

	while (1)
	{
		//TCP Loopback Test
		ProcessTCPServer(0, 5000);

		//UDP Loopback Test
		ProcessUDP(1, 3000);
	}		
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
void ProcessTCPServer(unsigned char Sock, unsigned int Port)
{
	#define MAX_BUF_SIZE	1460
	unsigned int len;							

	unsigned char data_buf[MAX_BUF_SIZE];

	
	switch(getSockStatus(Sock))
	{
	case SOCK_ESTABLISHED:
		//check Rx data
		if((len = getRecvSize(Sock)) > 0) 			
		{
			//if Rx data size is lager than TX_RX_MAX_BUF_SIZE 
			if (len > MAX_BUF_SIZE) len = MAX_BUF_SIZE;	
			
			//read the received data
			len = recv(Sock, data_buf, len);
			send(Sock, data_buf, len);  // send


		}		
		break;
		
	case SOCK_CLOSE_WAIT:                           		
		//If the client request to close
		disconnect(Sock);
		break;
		
   case SOCK_CLOSED:                   // CLOSED
		close(Sock);                        // close the SOCKET
		socket(Sock, Sn_MR_TCP, Port,0);   // open the SOCKET  
		break;
		
   case SOCK_INIT:                     // The SOCKET opened with TCP mode
		//connect(Sock, m_ConfigServerIp, port);
		listen(Sock);
		printf("%d : TCP Server(%d) Started.\r\n", Sock, Port);
		break;		
	}
}

void ProcessUDP(SOCKET Sock, unsigned int Port)
{
	uint32 len;
	uint8 destip[4];
	uint16 destport;

	unsigned char data_buf[MAX_BUF_SIZE];

	switch(getSn_SSR(Sock))
	{
		// -------------------------------
		case SOCK_UDP:                                     // 
			if((len=getSn_RX_RSR(Sock)) > 0)                   // check the size of received data
			{
				len = recvfrom(Sock,data_buf,len,destip,&destport);  // receive data from a destination
				if(len !=sendto(Sock,data_buf,len,destip,destport))  // send the data to the destination
				{
					printf("%d : Sendto Fail.len=%ld,",Sock,len);
					printf("%d.%d.%d.%d(%d)\r\n",destip[0],destip[1],destip[2],destip[3],destport);
				}
			}
		break;
		 // -----------------
		case SOCK_CLOSED:                                  // CLOSED
			close(Sock);                                       // close the SOCKET
			socket(Sock,Sn_MR_UDP,Port,0);                  // open the SOCKET with UDP mode
			break;
		
		default:
			break;
		}
	}
//-----------------------------------------------------------------------------
