/*
 * RECEIVER2.cpp
 *
 * Created: 12/1/2017 2:14:55 PM
 * Author : Prashant
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

static volatile uint16_t timer ;
unsigned long int p=0;

int main(void)
{
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	DDRC = 0x00;
	DDRA = 0xFF;
	sei();
	TCCR1B = 0x01 ;
	TCNT1 = 0 ;
	EIMSK |= (1<<INT0) ;
	EICRA |= (1<<ISC00) | (1<<ISC01);
	while (1)
	{
		uart_putint(timer);
		_delay_ms(100);
		if (timer > 20000)
		{
			uart_puts("low\n");
			PORTA =  0x01;
		}
		else
		{
			uart_puts("high\n");
			PORTA = 0x02;
		}
	}
	return 0;
}

ISR (INT0_vect)
{
	timer = TCNT1;
	p++;
	TCNT1 = 0x00;
}



