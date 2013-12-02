/**
 @file		evb.c
 @brief 		functions to initialize EVB prepheral equipments
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

#include "../mcu/types.h"
#include "../mcu/serial.h"
#include "../evb/evb.h"
#include "../evb/config.h"
#include "../evb/lcd.h"
#include "../mcu/delay.h"

#define	ATMEGA128_0WAIT		0
#define	ATMEGA128_1WAIT		1
#define	ATMEGA128_2WAIT		2
#define	ATMEGA128_3WAIT		3
#define 	ATMEGA128_NUM_WAIT	ATMEGA128_1WAIT


static u_char evb_lcd_text[LCD_MAX_ROW][LCD_MAX_COL+1];
extern SYSINFO	SysInfo;

void evb_set_lcd_text(u_char row, u_char* lcd)
{
	if(row < LCD_MAX_ROW && strlen((char*)lcd) <= LCD_MAX_COL)
	{
		memset(evb_lcd_text[row],' ',LCD_MAX_COL);
		evb_lcd_text[row][LCD_MAX_COL] = 0;
		memcpy(evb_lcd_text[row],lcd,strlen((char*)lcd));
		lcd_gotoxy(0,row);
		lcd_puts((char*)evb_lcd_text[row]);
	}
}


/**
 * @brief	Initialize EVB prepheral equipments( MCU, LCD, UART,... )
 */ 
void evb_init(void)
{
	AdcInit();
	mcu_init();	

	lcd_init();	
						//0123456789abcdef 	
	evb_set_lcd_text(0,(u_char *)"WebSerberAK v1.4");
	evb_set_lcd_text(1,(u_char *)"Initialize...   ");	
	
	uart_init(0, 7);		// Serial Port Initialize

	sw_init();

	led_init();
}



void mcu_init(void) 
{
	cli();
		
#ifndef __DEF_IINCHIP_INT__	
	EICRA=0x00;
	EICRB=0x00;
	EIMSK=0x00;
	EIFR=0x00;
#else
	EICRA = 0x00;			// External Interrupt Control Register A clear
	EICRB = 0x02;			// External Interrupt Control Register B clear // edge 
	EIMSK = (1 << INT4);		// External Interrupt Mask Register : 0x10
	EIFR = 0xFF;			// External Interrupt Flag Register all clear
	DDRE &= ~(1 << INT4);		// Set PE Direction 
	PORTE |= (1 << INT4);		// Set PE Default value
#endif


#if (ATMEGA128_NUM_WAIT == ATMEGA128_0WAIT)
	MCUCR = 0x80;		
	XMCRA=0x40;
#elif (ATMEGA128_NUM_WAIT == ATMEGA128_1WAIT)
	MCUCR = 0xc0;		// MCU control regiseter : enable external ram
	XMCRA=0x40;		// External Memory Control Register A : 
						// Low sector   : 0x1100 ~ 0x7FFF
						// Upper sector : 0x8000 ~ 0xFFFF
#elif (ATMEGA128_NUM_WAIT == ATMEGA128_2WAIT )
	MCUCR = 0x80;
	XMCRA=0x42;
#elif ((ATMEGA128_NUM_WAIT == ATMEGA128_3WAIT)
	MCUCR = 0xc0;
	XMCRA=0x42;
#else
#error "unknown atmega128 number wait type"
#endif	

	sei();				// enable interrupts
}



//-----------------------------------------------------------------------------
//EVB Switch Control
void led_init(void)
{
	u_int i;
	LED_AVR_PORT_DIR |= (1<<LED_PIN_0) | (1<<LED_PIN_1) | (1<<LED_PIN_2) | (1<<LED_PIN_3);
	
	for(i = 0; i < 4; i++)
	{
		led_off_all();
		led_on(i);
		wait_10ms(40);
	}
	
	led_off_all();
}

void led_toggle(u_char led)
{
	if(led_state(led)==LED_ON)
		LED_AVR_PORT_VAL &= ~(1 << (LED_PIN_0+led));
	else 	LED_AVR_PORT_VAL |= (1 << (LED_PIN_0+led));
}

void led_off(u_char led)
{
	LED_AVR_PORT_VAL |= (1 << (LED_PIN_0+led));
}

void led_on(u_char led)
{
	LED_AVR_PORT_VAL &= ~(1 << (LED_PIN_0+led));	
}

u_char led_state(u_char led)
{
	return ( ( (LED_AVR_PORT_VAL & (1 << (LED_PIN_0+led)))) ? LED_OFF : LED_ON);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//EVB Switch Control
void sw_init(void)
{
	//port pull up
	SW_AVR_PORT_VAL |= SW_MASK;
	SW_AVR_PORT_DIR &= ~(SW_MASK);
}

u_char sw_state(unsigned char num)
{
	//SwNum
	unsigned char ret;
	ret = SW_VALUE & (1<<(SW_PIN_0+(num)));
	return ((ret)?1:0);
}
//-----------------------------------------------------------------------------



u_char* evb_get_lcd_text(u_char row)
{
	if(row < LCD_MAX_ROW)
		return evb_lcd_text[row];
	return 0;
	
}



void ADC_Initialize(void);

//------------------------------------------------------------------------------
// Function Routine
//ADC Initialize
void AdcInit(void)
{
	ADMUX = 0;
    ADCSR = ADC_ENABLE | ADC_PRESCALE_DIV32;
}

//Read ADC Value
unsigned int AdcRead(unsigned char port)
{
	unsigned int value = 0;

	ADMUX = port&7;
	ADCSR |= ADC_START_CONVERSION;

	while(!(ADCSR & ADC_COMPLETE));

	value = ADCL;
	value = (ADCH<<8) | value;
	
	return value;
}


void evb_soft_reset(void)
{
//	set_reset_flag(SYSTEM_AUTO_RESET);
	asm volatile("jmp 0x0000");	
}
