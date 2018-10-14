/*
 * UnicaitProject.c
 *
 * Created: 7/25/2018 4:54:06 PM
 * Author : VladBaciu
 */ 
#define F_CPU 16000000L 
#define BAUD 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "UART.h"
#include "ADC.h"
#include "LCD_driver.h"
#include "PWM.h"
#define THRESHOLD	 80
#define ADC_PIN	 0

volatile unsigned char  data;
volatile  uint16_t potVal=0;
volatile int flag=0;

void init_timer1();
void init_timer0();




int main(void)
{
	DDRB |= (1<<PINB0); 
	PORTB &= ~(1<<PINB0);
	
	//init_timer1();
	init_timer0();
	uart_init(BAUD,F_CPU);
	adc_init();
	init_PWM();
	init_LCD();
	sei();
    stdout = &uart_output;
	LCD_String("Proiect-B. Vlad ");
	_delay_ms(1000);
	
	
	char *valueForLcd=malloc (sizeof(char) * 10);
	long valToShow;
	long newValue;
  for (;;) {
	
	    
		
		 newValue=potVal*64;
		OCR1A=newValue;
		 valToShow = mapVal(potVal,0,1023,0,100);
		sprintf(valueForLcd,"PWM=%ld %%  ",valToShow);
		LCD_String_xy(1,4,valueForLcd);
		
		
		//LCD_Clear();
		
		
		
  }
  return 0;
}
//void init_timer1()
//{
	//
	//// ****************start INIT TIMER 1-transmit sensor data at 1m**************   //
	//
	 //OCR1A = 0x3D08;
	 //TCCR1B |= (1 << WGM12);
	 //TIMSK1 |= (1 << OCIE1A);
	 //TCCR1B |= (1 << CS12) | (1 << CS10);  //15.6 khz
	//// ****************stop INIT TIMER 1**************   //
//
//
//}
//ISR (TIMER1_COMPA_vect)
//{
	//
//}
void init_timer0()
{
	TCCR0A = (1 << WGM01);
	OCR0A = 195.3;
	TIMSK0 = (1 << OCIE0A);
	TCCR0B = (1 << CS02) | (1 << CS00);
}


ISR(TIMER0_COMPA_vect)
{
	
	potVal=adc_read(ADC_PIN);
	
}

ISR(USART_RX_vect) {
	data = UDR0;
	flag=1;
}

