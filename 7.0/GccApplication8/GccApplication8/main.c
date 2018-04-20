/*
 * GccApplication8.c
 *
 * Created: 11/18/2017 4:30:37 PM
 * Author : Prashant
 */ 
#define F_CPU 1000000
#include <avr/io.h>
int main(void)
{
	DDRA = 0b00000010;
	PORTA = 0b00000001;
   
    while (1) 
    {
		if (bit_is_clear(PINA,1))
		{
			PORTA |=0b00000010;
		}
		else
		{
			PORTA = 0b00000001;
		}
    }
	
}

