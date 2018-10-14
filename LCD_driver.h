/*
 * LCD_driver.h
 *
 * Created: 10/14/2018 5:16:26 PM
 *  Author: VladBaciu
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#define RS 2
#define E 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7

void setPins();
void init_LCD();
void LCD_Send4bitCmd(uint8_t cmnd);
void LCD_Command(uint8_t cmnd);
void LCD_Send4bitData(uint8_t cmnd);
void LCD_Data(uint8_t cmnd);
void LCD_Clear();
void LCD_String(uint8_t *str);
void LCD_String_xy(uint8_t row, uint8_t pos, uint8_t *str);

#endif /* LCD_DRIVER_H_ */