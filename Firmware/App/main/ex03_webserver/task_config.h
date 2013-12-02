#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#define EEPOP						0
#define SPECIALOP					0x82

#define VER_H						1
#define VER_L						4
#define SOCK_CONFIG					3
#define EEPADDR_VER					4

#define SBUF_LENGTH					253

// Special char values
#define CR                 			0x0D
#define LF                 			0x0A

#define CONFIG_CLIENT_PORT			48713  
#define CONFIG_SERVER_PORT			48714  
#define CONFIG_UP_PORT				48715


typedef struct
{
	unsigned char op[4];		//0 ~ 3
	unsigned char ver[2];		//4 ~ 5
	unsigned char mac[6];		//6 ~ 11
	unsigned char ip[4];		//12 ~ 15
	unsigned char subnet[4];	//16 ~ 19
	unsigned char gw[4];		//20 ~ 23
	unsigned char dhcp;			//24
	unsigned char myMac[6]; 	//25 ~ 30	//the old mac address; Ver 1.3; 2010.02.08
} StrConfigParam;


//for testing
#define DefConfigParam			"\x82\x82\x82\x82\x00\x00\x00\x08\xDC\x00\x00\x00\xC0\xA8\x00\x03\xFF\xFF\xFF\x00\xC0\xA8\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x08\xDC\x00\x00\x00"
//#define DefConfigParam		"\x82\x82\x82\x82\x00\x00\x00\x08\xDC\x11\x12\x58\xC0\xA8\x01\x65\xFF\xFF\xFF\x00\xC0\xA8\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"


#define GoBoot()	do{								\
						MCUCR |= _BV(IVCE);			\
						MCUCR |= _BV(IVSEL);		\
						((void (*)())0x1e000)();	\
					}while(0)

#define GoApp()		do{								\
						MCUCR |= _BV(IVCE);			\
						MCUCR &= ~_BV(IVSEL);		\
						((void (*)())0x0000)();		\
					}while(0)					
//-----------------------------------------------------------------------------
void default_network(void);
void SetConfig(void);
void ProcessConfig(unsigned char Sock);
void write_end_page(void);
