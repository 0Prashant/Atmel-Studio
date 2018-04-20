
/*
 * GccApplication3.c
 *
 * Created: 20/05/2017 11:06:26 PM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int p=0;
	DDRD = 0x03;
	PORTD = 0b00000101;
	
    while (1) 
       {
		   PORTD |= 0b00000100;
		if((bit_is_clear(PIND,2)))
		{
			if (p==0)
			{
				PORTD ^= 0x01;
				PORTD ^=0x02;
			}
		p=1;	
		}
		else
		{
			p=0;
		}
    }
	return 0;
}



