/*
 * Ram Dai.cpp
 *
 * Created: 1/22/2018 5:41:55 PM
 * Author : Prakash Chaudhary
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int count;

int main(void)
{
	TCCR1A |= (1<<COM1A0);
	TCCR1B |= (1<<CS12)|(1<<CS10)|(1<<WGM02);
	TIMSK1 |= (1<<OCIE1A);
	TIFR1 |= (1<<OCF1A);
	OCR1A = 31248;
	/////////////////////////////////////////////////////////////
	DDRD = 0b00110000;
	DDRB	= 0xff;
	//DDRD &= ~(1<<PD0);
	//DDRD &= ~(1<<PD1);
	//DDRD |= (1<<PD4) | (1<<PD5);
	PORTD |= (1<<PIND0);
	PORTD &= ~(1<<PIND1);
	PORTB = 0x00;
	/////////////////////////////////////////////////////////////
	EICRA |= (1<<ISC01)|(1<<ISC10)|(1<<ISC11);
	EIMSK |= (1<<INT0)|(1<<INT1);
	EIFR |= (1<<INTF0)|(1<<INTF1);
	////////////////////////////////////////////////////////////////
	sei();
    /* Replace with your application code */
    while (1) 
    {
		
    }
}
ISR(INT0_vect)
{
	PORTB ^= (1<<0);
}
ISR(INT1_vect)
{
	PORTB |= (1<<1);
}
ISR(TIMER1_COMPA_vect)
{
		PORTB &= ~(1<<1);
	
}

