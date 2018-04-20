/*
 * test_avr_lib.cpp
 *
 * Created: 3/9/2018 12:17:35 PM
 * Author : Rishav
 */ 

#include "basics/AVR.hpp"
#include "pphls/PWM.hpp"


int main(void)
{
	DDRB   |= (1<<PINB5);
	HardwarePWM<PWM::Phase_PWM> pwm1(PWM::_1);
	
	pwm1.set_frequency(4000);
	pwm1.set_prescale(256);
	pwm1.set_duty_cycle<PWM::_A>(133);
	
    	
		
	
		
			uint16_t freq1 = 4000;
			uint16_t preScale1 = 256;
			uint8_t dutyCycle1A = 50 ;
			TCCR1B |= (1<<CS12)|(0<<CS11)|(0<<CS10);
			
			OCR1A |= (1<<WGM11)|(0<<WGM10);
			TCCR1B |= (1<<WGM13)|(0<<WGM12);
 			ICR1   = (F_CPU/(freq1*preScale1)-1);
 			OCR1A = ((F_CPU/(freq1*preScale1)-1)*dutyCycle1A)/100; /*Update value for OC1A*/
			DDRB   |= (1<<PINB5);
        	TCCR1A |= (1<<COM1A1)|(0<<COM1A0);
		
		
		
		
	while (1) 
    {
    }
}

