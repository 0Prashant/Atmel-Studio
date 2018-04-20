/*
 * stepperdrive.cpp
 *
 * Created: 2/9/2018 4:09:02 PM
 * Author : Prashant
 */ 


#define F_CPU 16000000UL

#include<util\delay.h>
#include "pinModes.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#define sampTime 0.0005 //  In seconds less than 4 secs

#define motorx_Step       C,4
#define motorx_Direction  C,5
#define motory_Step	      C,2
#define motory_Direction  C,3



int main(void)
{
    /* Replace with your application code */
    OUTPUT(motorx_Direction);
    OUTPUT(motorx_Step);
    OUTPUT(motory_Direction);
    OUTPUT(motory_Step);
   
 
    
    TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);  // 1024 prescale and CTC mode
    TIMSK  |= (1<<OCIE1A);                         // Compare interrupt enable
    OCR1A   = (15624*sampTime);		           // 15624 -> 1 sec
   sei();
    while (1)
    {
    _delay_ms(10000);
	SET(motorx_Direction);
	SET(motory_Direction);
	_delay_ms(10000);
	CLEAR(motorx_Direction);
	CLEAR(motory_Direction);
    }
}

ISR(TIMER1_COMPA_vect){
	
     TOGGLE(motorx_Step);
     TOGGLE(motory_Step);
  				
}






