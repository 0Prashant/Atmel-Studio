/*
 * motorandPWM.cpp
 *
 * Created: 10/11/2017 3:13:53 PM
 * Author : Sampada
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
  volatile  uint8_t duty_cycle = 0;
	
	int P_Scale;
	int i;
	int required_frequency;
	DDRD|=(1<<PIND5);
	
	TCCR1A|=(1<<COM1A1)|(1<<WGM11);
	TCCR1B |=(1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
	
	P_Scale = 64;
	required_frequency= 4000;
	ICR1 = (F_CPU/P_Scale*required_frequency)-1;
	
    while (1) 
    {
		
		
		   /*duty_cycle ++;*/
		   
			_delay_ms(50);
			
			for (i=0;i<100;i++){
				duty_cycle++;
				OCR1A = (ICR1/100)*duty_cycle;
			}
		
			if (i == 100){
				
				for (i=100;i=0;i--){
					duty_cycle--;
					OCR1A = (ICR1/100)*duty_cycle;
				}
			
			}
	}

}