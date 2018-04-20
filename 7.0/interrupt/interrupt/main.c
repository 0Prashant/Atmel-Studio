/*
 * interrupt.c
 *
 * Created: 28/05/2017 11:15:06 PM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
	unsigned char temp;
	DDRD = 0xFF;
	DDRC = 0xFF;
	DDRB = 0x00;
	PORTB = 0x00;
	TCCR1B = 0x03;
	TCNT1 = 50000;
	PORTC = 0x00;
    sei();
	TIMSK = 1<<TOIE1 ;
    while (1) 
    {
		temp = PINB;		
		PORTD = temp;
		PORTD =0x00;
		
    }
	return 0;
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = 50000;
	PORTC ^= 0xFF;
	
}