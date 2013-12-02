#include <avr/io.h>
#include "serial.h"

void initUart(void){
	/* set baud rate */
	UBRR0H = (uchar) (UART_BAUD_SELECT>>8);
	UBRR0L = (uchar) UART_BAUD_SELECT;

	/* Enable UART receiver and transmitter */
	UCSR0A = ( 1 << U2X0 );
	UCSR0B = ( 1 << TXEN0 ); 

//	fdevopen((void*)USART0_Transmit, (void*)USART0_Receive);
}

void USART0_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !(UCSR0A & (1<<UDRE0)) )
		; 			                
	/* Start transmittion */
	UDR0 = data; 			        
}

void putStr(unsigned char* data)
{
	for(;*data;) USART0_Transmit(*(data++));
}

void putData(unsigned char* data, uint len)
{
	uchar temp, hn, ln, lf;
	uint i;

	lf = 0;
	for(i = 0; i < len; i++) {
		temp = *(data++);

		hn = (temp >> 4);
		if(hn > 9) hn += ('a' - 10);
		else hn += 0x30;

		ln = (temp & 0x0f);
		if(ln > 9) ln += ('a' - 10);
		else ln += 0x30;

		USART0_Transmit(hn);
		USART0_Transmit(ln);
		USART0_Transmit(' ');

		if(lf == 16) {
			lf = 0;
			USART0_Transmit('\r');
			USART0_Transmit('\n');
		}
		else lf++;
	}
}
