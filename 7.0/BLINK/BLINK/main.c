/*
 * BLINK.c
 *
 * Created: 11/18/2017 2:42:06 PM
 * Author : Prashant
 */ 
#define  F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRA = 0b00000001;
	
    while (1) 
    {
		PORTA = 0b00000001;
		_delay_ms(1000);
		PORTA = 0b00000000;
		_delay_ms(1000);
		
    }
}

