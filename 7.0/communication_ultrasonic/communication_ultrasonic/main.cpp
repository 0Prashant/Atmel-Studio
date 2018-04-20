/*
 * communication_ultrasonic.cpp
 *
 * Created: 12/22/2017 9:53:37 AM
 * Author : Prashant
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <math.h>
#include "uart0.h"

#define echo 2
#define trigger 3

unsigned  char i;
int16_t value = 0;

void start_timer()
{
	TCCR1B = 0x01;
	TCNT1 = 0;
	i=0;	
}

void stop_timer()
{
	value = TCNT1;
	TCCR1B = 0x00;
	TCNT1 = 0;
	i=1;
}

void trigger_ultrasonic()
{
	PORTD = 0<<trigger;
	_delay_us(1);
	PORTD |= 1<<trigger;
	_delay_us(12);
	PORTD |= 0<<trigger;
	_delay_us(1);
	//PORTD = 1<<echo;
}
void read_ultrasonic()
{
	int16_t distance_in_cm;
	int16_t final;
	char distance_in_char[5];
	while((PIND2 != 1))
		{
		}
	while(~(PIND2 != 1))
		{
		}
	distance_in_cm = ((value / 60)) ;
	final = distance_in_cm;
	itoa(final,distance_in_char,10);
	UART0_writes("  DISTANCE = ");
	UART0_writes(distance_in_char);
	UART0_writes("\n");
}

int main(void)
{
	UART0_init(9600);
	i=1;
	DDRD |=1<<trigger;
	DDRD &= ~(1<<echo);
	
	sei();
	EICRA = 1<< INT0;
	MCUCR |= (1<< ISC00);
	TCCR1B |= (1<<CS10) ;
	
	UART0_writes("**********...Initializing ultrasonic module...**********");
	while (1)
	{
		trigger_ultrasonic();
		read_ultrasonic();
		_delay_ms(200);
 	}
	return 0;
}
ISR (INT0_vect)
{
	if (i==1)
	{
		start_timer();
	}
	else
	{
		stop_timer();
	}
}

