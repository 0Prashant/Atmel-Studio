/*
 * megaPinChange.cpp
 *
 * Created: 1/8/2018 10:51:28 PM
 * Author : Sherlock
 */

#include <avr/io.h>
#include<avr/interrupt.h>
#include "pinChange.h"

int main(void)
{
    DDRB |= (1<<PINB7);

    /* Replace with your application code */
   pinChangeOne_init();
   setPin(1,9);
    while (1)
    {
    }
}

ISR(PCINT1_vect){
	PORTB ^= (1<<PINB7);
}
