/*
*
@file		lcd.h
@brief	LCD Basic Function Definition
*/

#ifndef _LCD_H
#define _LCD_H


#define LCD_MAX_COL		16
#define LCD_MAX_ROW		2

#define LCD_BASEADDR		0x9000
#define LCD_DELAY				120

#define	Sbi(Port, Bit)					Port |= Bit
#define	Cbi(Port, Bit)					Port &= ~(Bit)
#define BM(Num)							(1<<Num)

//LCD
#define LCD_RS_PORT						PORTE
#define LCD_RS_DDR						DDRE
#define LCD_RS_BIT						BM(2)

#define LCD_WR_PORT						PORTE
#define LCD_WR_DDR						DDRE
#define LCD_WR_BIT						BM(3)

#define LCD_CS_PORT						PORTE
#define LCD_CS_DDR						DDRE
#define LCD_CS_BIT						BM(7)

#define LCD_DATA_PORT					PORTD
#define LCD_DATA_DDR					DDRD



#define LCD_RW_INIT()					Sbi(LCD_WR_DDR, LCD_WR_BIT)
#define LCD_RWON()						Sbi(LCD_WR_PORT, LCD_WR_BIT)	
#define LCD_RWOFF()						Cbi(LCD_WR_PORT, LCD_WR_BIT)

#define LCD_RS_INIT()					Sbi(LCD_RS_DDR, LCD_RS_BIT)
#define LCD_RSON()						Sbi(LCD_RS_PORT, LCD_RS_BIT)	
#define LCD_RSOFF()						Cbi(LCD_RS_PORT, LCD_RS_BIT)

#define LCD_EN_INIT()					Sbi(LCD_CS_DDR, LCD_CS_BIT)
#define LCD_ENABLE()					Sbi(LCD_CS_PORT, LCD_CS_BIT)
#define LCD_DISABLE()					Cbi(LCD_CS_PORT, LCD_CS_BIT)

#define LCD_DATA(Data)					LCD_DATA_PORT = (LCD_DATA_PORT&0x0F) | (Data&0xF0);LCD_ENABLE();LCD_DISABLE();LCD_DATA_PORT = (LCD_DATA_PORT&0x0F)| ((Data<<4)&0xF0);	
	

//LCD Set System
#define LCD_SET_SYSTEM          0x20
#define LCD_SYS_8BIT            0x10
#define LCD_SYS_4BIT            0x00
#define LCD_SYS_2LINE           0x08

//LCD Set Cursor Shift
#define LCD_SET_CUR_SHIFT       0x10
#define LCD_DISPLAY_SHIFT       0x08    //if bit clear -> Cursor Shift 
#define LCD_SURSOR_SHIFT_RIGHT  0x04    //if bit clear -> Left Shift

//LCD Set Display
#define LCD_SET_DISPLAY         0x08
#define LCD_DISP_DISPLAY_ON     0x04
#define LCD_DISP_CURSOR_ON      0x02
#define LCD_DISP_CURSOR_FLASH   0x01

//LCD Set Input Mode
#define LCD_INPUT_MODE          0x04
#define LCD_INPUT_INCRENENT	    0x02    //if bit clear -> input decrement	
#define LCD_INPUT_SHIFT         0x01

#define LCD_CURSOR_HOME         0x02
#define LCD_CLEAR               0x01
#define LCD_SET_CGRAM           0x40
#define LCD_SET_DDRAM           0x80	
	
/* If there are unused functions in program and on compiling with Keil-C, it result in warning.In this reason, wrong operation could be happend.
So it prevent to compile unused functions to use define-function.
*/
#define __LCD_UNUSED   /**< If defined with " __LCD_UNUSED", actually it's not to be compiled "__LCD_UNUSED Block" */


extern char lcd_ready(void);			// Check for LCD to be ready
extern void lcd_clrscr(void);			// Clear LCD. 
extern char lcd_init(void);			// LCD Init
extern void lcd_gotoxy(u_char x, u_char y);	// Output character string in current Cursor.
extern char* lcd_puts(char* str);		// Output character stream in current Cursor.
extern void lcd_putch(char ch);		// Output 1 character in current Cursor.



#ifndef __LCD_UNUSED

extern void lcd_home_cursor(void);		// Move Cursor first Column.
extern void lcd_set_cursor_type(u_char type);	// Decide Cursor type.
extern void lcd_shitf_cursor(u_char dir);	// Shift to Left and Right current Cursor.

#endif

#endif
