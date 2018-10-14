/*
 * LCD_driver.c
 *
 * Created: 10/14/2018 5:16:11 PM
 *  Author: VladBaciu
 */ 
#include <util/delay.h>
#include "LCD_driver.h"
#include <avr/io.h>
void init_LCD()
{
	setPins();
	_delay_ms(20); // Wait for more than 15 ms after VCC rises to 4.5 V
	LCD_Command(0x33);
	LCD_Command(0x32);	/* Send for 4 bit initialization of LCD  */
	LCD_Command(0x28);	/* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0c);	/* Display on cursor off */
	LCD_Command(0x06);	/* Increment cursor (shift cursor to right) */
	LCD_Command(0x01);	/* Clear display screen */
	
	
}

void LCD_Send4bitCmd(uint8_t cmnd) {             
	
	
	
	PORTD &= ~(1<<RS);
	//delay_ns(50);
	PORTD  |= (1<< E); /* Enable pulse */
	
	PORTD &=0x0F;

	//delay_ns(100);
	PORTD  |= (cmnd & 0xF0) | (1<<E); /* sending upper nibble */
	_delay_us(1);
	PORTD &= ~(1 << E);
	_delay_us(2);
}

void LCD_Command(uint8_t cmnd)
{
	LCD_Send4bitCmd(cmnd);

	_delay_us(2);

	LCD_Send4bitCmd(cmnd<<4);

	_delay_ms(20);
	
	
}

void LCD_Send4bitData(uint8_t cmnd) {
	
	PORTD |= (1<<RS);
	//delay_ns(50);
	PORTD  |= (1<< E); /* Enable pulse */
	
	PORTD &=0x0F;

	//delay_ns(100);
	PORTD  |= (cmnd & 0xF0) | (1<<E) | (1<<RS); /* sending upper nibble */
	_delay_us(1);
	PORTD &= ~(1 << E);
	_delay_us(2);
}
void LCD_Data(uint8_t cmnd)
{
	LCD_Send4bitData(cmnd);

	_delay_us(2);

	LCD_Send4bitData(cmnd<<4);

	_delay_ms(20);
	
	
}

void LCD_Clear() {
	LCD_Command(0x01); /* Clear display */
	_delay_ms(2);
	LCD_Command(0x01); /* Clear display */
}

void LCD_String(uint8_t *str) /* Send string to LCD function */
{
	int i;
	for (i = 0; str[i] != 0; i++) /* Send each uint8 of string till the NULL */
	{
		LCD_Data(str[i]);
	}
}
void LCD_String_xy(uint8_t row, uint8_t pos, uint8_t *str)
{
	
	if (row == 0 && pos < 16) {
		LCD_Command((pos & 0x0F) | 0x80); /* Command of first row and required position<16 */
		LCD_Command((pos & 0x0F) | 0x80);/* Command of first row and required position<16 */
	} else if (row == 1 && pos < 16) {
		LCD_Command((pos & 0x0F) | 0xC0); /* Command of second row and required position<16 */
		LCD_Command((pos & 0x0F) | 0xC0); /* Command of second row and required position<16 */
	}
	_delay_us(40);
	LCD_String(str);
	
	
}
void setPins()
{
	DDRD |= (1<<RS) | (1<<E) | (1<<D4) | (1<<D5) | (1<<D6) | (1<<D7);
	PORTD =0x00;

}