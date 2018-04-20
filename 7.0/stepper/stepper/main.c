/*
 * stepper.c
 *
 * Created: 27/09/2017 8:14:53 PM
 * Author : Sushma
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	while (1)
	{
		PORTA = 0x02;
		_delay_ms(5);
		PORTA = 0x04;
		_delay_ms(5);
		PORTA = 0x08;
		_delay_ms(5);
		PORTA = 0x016;
		_delay_ms(5);
	}
	return 0;
}


