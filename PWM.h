/*
 * PWM.h
 *
 * Created: 10/13/2018 10:39:02 PM
 *  Author: VladBaciu
 */ 


#ifndef PWM_H_
#define PWM_H_


void init_PWM();
void control_PWM (uint16_t data);
long mapVal (long x, long in_min, long in_max, long out_min, long out_max);

#endif /* PWM_H_ */