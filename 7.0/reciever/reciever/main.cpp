/*
 * reciever.cpp
 *
 * Created: 12/10/2017 12:06:21 PM
 * Author : Sherlock
 */ 

#define F_CPU		16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart0.h"

static volatile uint16_t counter;
static volatile uint16_t last_counter;

inline void initTimer1A()
{
	TCCR1A |= (0 << WGM11) | (0 << WGM10);
	TCCR1B |= (0 << WGM13) | (1 << WGM12);		// CTC Mode

	OCR1A = 62499;
	
	TIMSK1 |= (1 << OCIE1A);

	TCCR1B |= (1 << CS12);		// Pre-Scaler = 256
}

int main(void)
{
	DDRD &= (1 << PD2);
	PORTD |= (1 << PD2);
	sei();
	char str[6];
	DDRB |= 0x01;
	UART0_init(9600);
	EICRA |= (1 << ISC01) | (1 << ISC00);
	EIMSK |= (1 << INT0);
	
	initTimer1A();
		
	while (1)
	{
		if(last_counter) {
			PORTB |= 0x01;
			if(last_counter > 40)
			last_counter = 0;
		}
	}
}

ISR(INT0_vect)
{
	++counter;
}

ISR(TIMER1_COMPA_vect)
{
	last_counter = counter;
	counter = 0;
}

