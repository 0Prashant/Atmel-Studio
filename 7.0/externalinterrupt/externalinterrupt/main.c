/*
 * externalinterrupt.c
 *
 * Created: 29/05/2017 11:18:28 PM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRC = 0xFF;
	
	sei();
	MCUCR = 0x01;
	GICR = 1 << INT0;
    while (1) 
    {
    }
	return 0;
}
ISR(INT0_vect)
{
	PORTC ^= 0xFF;
	
}

