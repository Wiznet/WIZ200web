#include <stdio.h>
#include <string.h>
#include "../../mcu/types.h"
#include "../../iinchip/socket.h"
#include "../../util/wiz_util.h"

#include "task_config.h"

StrConfigParam NetworkParam, MSGConfig;
extern unsigned char m_FlagFlashWrite;


extern void InitFlash(void);
//-----------------------------------------------------------------------------
void default_network(void)
{
//	unsigned long ip;

	memcpy(&NetworkParam, DefConfigParam, sizeof(NetworkParam));
	
	eeprom_write_block(&NetworkParam, (unsigned char*)EEPOP, sizeof(NetworkParam));
	eeprom_write_byte((unsigned char*)EEPADDR_VER, VER_H);
	eeprom_write_byte((unsigned char*)(EEPADDR_VER+1), VER_L);
}


//-----------------------------------------------------------------------------
void SetConfig(void)
{
	unsigned char temp;

	// Get Network Parameters
	temp = eeprom_read_byte((unsigned char*)EEPOP);

	
	if( temp != SPECIALOP) 
	{
		// This board is initial state
		default_network();
	}
	else
	{
		eeprom_read_block(&NetworkParam, (unsigned char*)EEPOP, sizeof(NetworkParam));
		//check version
		if( (eeprom_read_byte((unsigned char*)EEPADDR_VER) != VER_H) || (eeprom_read_byte((unsigned char*)(EEPADDR_VER+1)) != VER_L) ) {
			eeprom_write_byte((unsigned char*)EEPADDR_VER, VER_H);
			eeprom_write_byte((unsigned char*)(EEPADDR_VER+1), VER_L);
		}
		NetworkParam.ver[0] = VER_H;
		NetworkParam.ver[1] = VER_L;
	}

	setSIPR(NetworkParam.ip);
	setGAR(NetworkParam.gw);
	setSUBR(NetworkParam.subnet);
	setSHAR(NetworkParam.mac);
	
	
}
//-----------------------------------------------------------------------------


//UDP
void ProcessConfig(unsigned char Sock)
{
	int len;							
	unsigned char serverip[4];
	uint16 serverport = CONFIG_SERVER_PORT;
	
	switch (getSn_SR(Sock))
	{
		case SOCK_UDP:
			if((len = getSn_RX_RSR(Sock)) > 0)
			{
				if(len > sizeof(MSGConfig))len = sizeof(MSGConfig);

				len = recvfrom(Sock, (unsigned char*)&MSGConfig, len, serverip, &serverport);
				//memcpy(m_ConfigServerIp, serverip, 4);
				
				if(serverport == CONFIG_SERVER_PORT)
				{
					if(memcmp((unsigned char*)MSGConfig.op, (unsigned char*)"FIND", 4)==0)
					{
						
						MSGConfig = NetworkParam;
						memcpy((unsigned char*)MSGConfig.op, "find", 4);

						serverip[0] = 0xff;serverip[1] = 0xff;serverip[2] = 0xff;serverip[3] = 0xff;
						sendto(Sock, (unsigned char*)&MSGConfig, sizeof(MSGConfig), serverip, serverport);

						//printf("Find Command.\r\n");
					}			
					else if(memcmp((unsigned char*)MSGConfig.op, (unsigned char*)"SETT", 4)==0)
					{
						if ((MSGConfig.mac[0]==NetworkParam.mac[0]) && (MSGConfig.mac[1]==NetworkParam.mac[1]) && (MSGConfig.mac[2]==NetworkParam.mac[2]) && (MSGConfig.mac[3]==NetworkParam.mac[3]) && (MSGConfig.mac[4]==NetworkParam.mac[4]) && (MSGConfig.mac[5]==NetworkParam.mac[5]))
						{
							memcpy((unsigned char*)MSGConfig.op, "sett", 4);
							serverip[0] = 0xff;serverip[1] = 0xff;serverip[2] = 0xff;serverip[3] = 0xff;
							sendto(Sock, (unsigned char*)&MSGConfig, sizeof(MSGConfig), serverip, serverport);

							MSGConfig.op[0] = SPECIALOP;
							MSGConfig.op[1] = SPECIALOP;
							MSGConfig.op[2] = SPECIALOP;
							MSGConfig.op[3] = SPECIALOP;
							eeprom_write_block(&MSGConfig, (unsigned char*)EEPOP, sizeof(MSGConfig));
							//eeprom_write_block(&MSGConfig, (unsigned char*)EEPOP + 12  , 13);
							// Need reboot
							close(Sock);

							//printf("Set Command.\r\n");
							cli();
							((void (*)())0x0000)();		// reset
						}
					}
					else if(memcmp((unsigned char*)MSGConfig.op, (unsigned char*)"FWUP", 4)==0)

					{
					
						if ((MSGConfig.mac[0]==NetworkParam.mac[0]) && (MSGConfig.mac[1]==NetworkParam.mac[1]) && (MSGConfig.mac[2]==NetworkParam.mac[2]) && (MSGConfig.mac[3]==NetworkParam.mac[3]) && (MSGConfig.mac[4]==NetworkParam.mac[4]) && (MSGConfig.mac[5]==NetworkParam.mac[5]))
						{
							cli();
							GoBoot();	// go to Boot
						}
					
					}					
					else if(memcmp((unsigned char*)MSGConfig.op, (unsigned char*)"RFUP", 4)==0) // webpage upload
					{
						if ((MSGConfig.mac[0]==NetworkParam.mac[0]) && (MSGConfig.mac[1]==NetworkParam.mac[1]) && (MSGConfig.mac[2]==NetworkParam.mac[2]) && (MSGConfig.mac[3]==NetworkParam.mac[3]) && (MSGConfig.mac[4]==NetworkParam.mac[4]) && (MSGConfig.mac[5]==NetworkParam.mac[5]))
						{
	//						InitFlash();
						
							m_FlagFlashWrite = 1;
						}
					}
					else if(memcmp((unsigned char*)MSGConfig.op, (unsigned char*)"SETM", 4)==0) // setting mac address
					{
						
						if ((MSGConfig.myMac[0]==NetworkParam.mac[0]) && (MSGConfig.myMac[1]==NetworkParam.mac[1]) && (MSGConfig.myMac[2]==NetworkParam.mac[2]) && (MSGConfig.myMac[3]==NetworkParam.mac[3]) && (MSGConfig.myMac[4]==NetworkParam.mac[4]) && (MSGConfig.myMac[5]==NetworkParam.mac[5]))
						{
							memcpy((unsigned char*)MSGConfig.op, "sett", 4);
							serverip[0] = 0xff;serverip[1] = 0xff;serverip[2] = 0xff;serverip[3] = 0xff;

							sendto(Sock, (unsigned char*)&MSGConfig, sizeof(MSGConfig), serverip, serverport);

							MSGConfig.op[0] = SPECIALOP;
							MSGConfig.op[1] = SPECIALOP;
							MSGConfig.op[2] = SPECIALOP;
							MSGConfig.op[3] = SPECIALOP;

							//recover the DHCP value; Ver 1.3; 2010.02.08
							MSGConfig.dhcp=NetworkParam.dhcp;
													
							eeprom_write_block(&MSGConfig, (unsigned char*)EEPOP, sizeof(MSGConfig));					

							printf("Set MAC Address Over.\r\n");
							// Need reboot
							close(Sock);

							cli();
							((void (*)())0x0000)();		// go to App
						}
					
					}					
				}
			}
			break;	
			
		case SOCK_CLOSED:     
			if(socket(Sock, Sn_MR_UDP, CONFIG_CLIENT_PORT, 0x00)== 0)
			//printf("Socket[%d] - Config Socket Started.\r\n", Sock);
			break;
	}	
}
//-----------------------------------------------------------------------------
