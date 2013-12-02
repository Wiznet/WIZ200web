/*
*
@file		lcd.c
@brief	LCD Basic Function Implement File

This source file is open, so it's easy to look for through Internet.\n
Do not need to controll LCD.
*/

#include "../mcu/types.h"
#include "../evb/lcd.h"

#define BUSY		0x80


void lcd_delay(unsigned int time)
{
    volatile unsigned int i, j;
    while(time)
    {
	    for(i=0;i<3;i++)
	    	for(j=0;j<1;j++);
	        	time--;
    }
}

/**
@brief	Check to be ready LCD.
@return 	If it's ready ,then '1',else then '-1'. If LCD Device is not insert actually,then return '-1'.
*/
char lcd_ready(void)
{
    volatile unsigned int i, j, time;
	time = LCD_DELAY;

	while(time)
    {
	    for(i=0;i<3;i++)
	    	for(j=0;j<1;j++);
	        	time--;
    }
	return 1;
}

void lcd_command(unsigned char Value)
{
	lcd_delay(LCD_DELAY);	//busy check		
	LCD_RSOFF();	
	LCD_RWOFF();

	LCD_DATA(Value);
	
	LCD_ENABLE();	
	LCD_DISABLE();
}

/**
 @brief		Clear LCD. 
*/
void lcd_clrscr(void)       
{
	lcd_ready();
	lcd_command(0x01);
}


void lcd_data(unsigned char ch)
{
	lcd_delay(LCD_DELAY);	//busy check		
	LCD_RSON();							//RS On
	LCD_RWOFF();	

	LCD_DATA(ch);

	LCD_ENABLE();	
	LCD_DISABLE();
}

/**
 @brief	Initialize LCD.
 @return 	If initialization is O.K, then return '1', else then return '0'. 
*/
char lcd_init(void)
{
	LCD_RW_INIT();
	LCD_RS_INIT();
	LCD_EN_INIT();
	LCD_DATA_DDR |= 0xF0;	
	
	LCD_DISABLE();
	LCD_RSOFF();	
	LCD_RWOFF();

	lcd_delay(LCD_DELAY+500);
	
    lcd_command(LCD_SET_SYSTEM | LCD_SYS_4BIT | LCD_SYS_2LINE);
    lcd_command(LCD_SET_CUR_SHIFT | LCD_DISPLAY_SHIFT | LCD_SURSOR_SHIFT_RIGHT);
    lcd_command(LCD_SET_DISPLAY | LCD_DISP_DISPLAY_ON);//| LCD_DISP_CURSOR_ON | LCD_DISP_CURSOR_FLASH);
	lcd_command(0x01);   
	lcd_command(LCD_CURSOR_HOME);
	
	lcd_delay(LCD_DELAY+4000);
	
	lcd_clrscr();
	lcd_gotoxy(0,0);
	return 1;
}


/**
 @brief		Move Cursor to X Column, Y Row.
  
 LCD to be offered by WIZnet is '2*16' Dimension, so Row(Argument y) is not above 1.
*/
void lcd_gotoxy(
	u_char x, 	/**< x - Column to move(INPUT) */
	u_char y		/**< y - Row to move(INPUT) */
	)
{
    lcd_ready();
    switch(y)
    {
        case 0 : lcd_command(0x80 + x); break;
        case 1 : lcd_command(0xC0 + x); break;
        case 2 : lcd_command(0x94 + x); break;
        case 3 : lcd_command(0xD4 + x); break;
    }
}


/**
 @brief		Output character string in current Cursor.
 @return 	Character string's Pointer to be output 
*/
char * lcd_puts(
	char* str		/**< str - Character to be output in LCD. (INPUT) */
	)
{
	unsigned char i;

	for (i=0; str[i] != '\0'; i++){
		lcd_ready();
		lcd_data(str[i]);
	}
	return str;
}


/**
 @brief		Output 1 character in current Cursor.
 @return 	Character string's Pointer to be output 
*/
void lcd_putch(
	char ch	/**< str - Character to be output in LCD. (INPUT) */
	)
{
	lcd_ready();
	lcd_data(ch);
}


#ifndef __LCD_UNUSED
/**
 @brief		Decide Cursor type.
*/
void lcd_set_cursor_type(
	u_char type	/**< type - Cursor type(INPUT) */
	)	
{
	lcd_ready();
	switch(type) 
	{
			//No Cursor 
	        case 0 : lcd_command(0x0C); break;  
			// Normal Cursor 
	        case 1 : lcd_command(0x0E); break; 
		// No Cursor | Blink
		case 2 : lcd_command(0x0D); break; 
			// Normal Cursor | Blink 
	        case 3 : lcd_command(0x0F); break; 
}


/**
 @brief		Shift to Left and Right current Cursor.
*/
void ShiftCursor(
	u_char dir	/**< dir - Decide direction to be Shift.(INPUT)  dir !=0  -> Right Shift, dir == 0 -> Left Shift */
	)	
{
	lcd_ready();
	lcd_command((dir ? 0x14: 0x10));
}


/**
 @brief		Move Cursor first Column.
*/
void lcd_home_cursor(void)       
{
	lcd_ready();
	lcd_command(2);
}

#endif
