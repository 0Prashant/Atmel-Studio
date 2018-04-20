/*
 * GccApplication5.c
 *
 * Created: 8/06/2017 3:24:39 PM
 * Author : Sushma
 */ 
#define  F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRA = 0xFF;
	PORTA = 0xFF;
	DDRB = 0xFF;
    PORTB = 0xFF;
    DDRC = 0xFF;
    PORTC = 0xFF;
    DDRD = 0xFF;
	PORTD = 0xFF;
    while (1) 
    {
    }
	return 0;
}

