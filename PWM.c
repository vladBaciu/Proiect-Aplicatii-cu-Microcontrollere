/*
 * PWM.c
 *
 * Created: 10/13/2018 10:38:31 PM
 *  Author: VladBaciu
 */ 
#include <avr/io.h>
void init_PWM()
{
	//fPWM = fclk_IO / (N * (1 + TOP))
	DDRB |= (1 << DDB1);
	

	ICR1 = 0xFFFF;
	// set TOP to 16bit

	OCR1A = 0xFFFF;




	TCCR1A |= (1 << COM1A1)|(1 << COM1B1);
	// set none-inverting mode

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
	
	
	TCCR1B |= (1 << CS10);
	// START the timer with no prescaler

}
long mapVal(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void control_PWM(uint16_t value)
{
	
	long newValue=mapVal(value,0,1023,0,65535);
	//printf("newVal %d",value);
	OCR1A=newValue;
}

