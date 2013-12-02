#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "types.h"

//#define CLK_CPU				8000000L	/* 16Mhz */
#define UART_BAUD_RATE		57600L		/* 57600 baud */
#define UART_BAUD_SELECT 	(CLK_CPU/(UART_BAUD_RATE*8L)-1L)

void initUart(void);

void USART0_Transmit( unsigned char data );
void putStr(unsigned char* data);
void putData(unsigned char* data, uint len);

#endif		/* _SERIAL_H_ */
