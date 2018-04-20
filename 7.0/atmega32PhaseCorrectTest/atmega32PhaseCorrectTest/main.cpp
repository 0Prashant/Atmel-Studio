/*
 * atmega32PhaseCorrectTest.cpp
 *
 * Created: 2/1/2018 3:39:13 PM
 * Author : Sherlock
 */

#define F_CPU 16000000UL
#include <avr/io.h>

int main(void)
{
	DDRB  = 0xff;
	PORTB= 0xff;



	TCCR1A |= (1<<WGM11) | (1<<COM1A1);
	TCCR1B |= (1<<WGM13) | (1<<CS11);




        ICR1  = 	249 ;
	OCR1A =         100 ;

    while (1)
    {

    }
}

