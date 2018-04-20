/*
 * proximity.cpp
 *
 * Created: 2/8/2018 1:55:52 PM
 * Author : Prashant
 */ 

#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include "uart.h"

int main(void)
{
	sei();
	initUART0();
    DDRH = 0x00;
	DDRE = 0x00;
	DDRF = 0xFF;
	PORTH = 0xFF;
	PORTE = 0xFF;
    while (1) 
    {
		if (bit_is_set(PINH, 5))
		{
			PORTF = 0x0F;
			UART0TransmitString("P1 on \t");
		}
		else
		{
			UART0TransmitString("P1 off \t");
			PORTF = 0x00;
		}
		if (bit_is_set(PINE, 3))
		{
			PORTF = 0xF0;
			UART0TransmitString("P2 on \n");
		}
		else
		{
			PORTF = 0x00;
			UART0TransmitString("P2 off \n");
		}
	_delay_ms(200);	
    }
	return 0;
}



