#ifndef __NETLOADING_H
#define __NETLOADING_H

#include "types.h"

#define SOCK_CONFIG			0
#define SOCK_POLY			1
#define SOCK_DATA			2
//
#define SOCK_DHCP			1

//#define SOCK_CONFIG_DIRECT	3
#define SOCK_WEB			3

/* UDP port numbers for Remote Configuration */
// 48780 48781 48782 48783
//#define	REMOTE_SERVER_PORT	48780	 //from Module to PC 
//#define REMOTE_CLIENT_PORT	48781	 //from PC to Module 
//#define REMOTE_CLIENT_PORT1	48782	 //from PC to Module 
#define REMOTE_UPDATE_PORT	48715	 //from PC to Module 

/* Remote msg message type */
#define	REMOTE_FIND		1
#define	REMOTE_SETT		2

#define REPLY_STATUS  			// STAT => replay STAT

#define CONFIG_MSG_SIZE		50	// temporary.. hard coding..

typedef struct _CONFIG_MSG
{
	unsigned long op;
	unsigned char Mac[6];
	unsigned long Lip;
	unsigned long Subnet;
	unsigned long Gw;
	unsigned int  LPort;
	unsigned int  SW_Ver;	
	unsigned char DHCP;	
	unsigned int  I_Time;	
}CONFIG_MSG;


#define EE_HEADER  0  			//
#define EE_MAC    (EE_HEADER+4) // MAC
#define EE_IA     (EE_MAC+6)    // IP addr
#define EE_SM     (EE_IA+4)  	// Subnet mask
#define EE_GW	  (EE_SM+4)	    // Gateway addr
#define EE_PORT   (EE_GW+4)	    // Port number
#define EE_VER    (EE_PORT+2)   // SW_Version
#define EE_DHCP   (EE_VER+2)    // DHCP 1 0n, 0 0ff
#define EE_INACTIVITY   (EE_DHCP+1)    // Inactivity time : 0~65535

#define EE_SIZE   (EE_INACTIVITY+2)

typedef union _IGM_INFO {
	CONFIG_MSG s;
	unsigned char c[CONFIG_MSG_SIZE]; 
} IGM_INFO;

int loading(void);

#endif
