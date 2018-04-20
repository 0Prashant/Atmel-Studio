/*
 * timer.c
 *
 * Created: 23/05/2017 1:01:28 PM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>


int main(void)
{
	DDRD = 0xFF;
	DDRC = 0xFF;
	unsigned char p,q;
	TCCR0 = 1<<CS12;
    while (1) 
    {
		if (TCNT0>250)
		{
			TCNT0 = 0;
			p++;
			q++;
			if (p>12)		
			{
				p=0;
				PORTD ^= 0b11111111;
			}
			if (p>12)
			{
				p=0;
				PORTD ^= 0b11111111;
			}
		}
    }
	return 0;
}

