/*
 * recieve.cpp
 *
 * Created: 11/26/2017 7:01:39 PM
 * Author : Prashant
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

static volatile uint16_t timer ;

int main(void)
{
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	DDRC = 0x00;
	DDRA = 0xFF;
	sei();
	TCCR1B = 0x01 ;
	TCNT1 = 0 ;
	EICRA |= (1<<ISC00) | (1<<ISC01); 
	EIMSK |= (1<<INT0) ;
	while (1)
	{
		uart_putint(timer);
		_delay_ms(100);
		if (timer > 20000)
		{
			uart_puts("low");
		 	PORTA =  0x01;
		}
		else
		{
			uart_puts("high");
		 	PORTA = 0x02;
		}
	}
	return 0;
}

ISR (INT0_vect)
{
	timer = TCNT1;
	TCNT1 = 0x00;
}