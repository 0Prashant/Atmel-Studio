/*
 * GccApplication2.c
 *
 * Created: 20/05/2017 6:21:19 PM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
int main()
{
    /* Replace with your application code */
	DDRD = 0b01111100;
    while (1)
	{
	if((PIND & 0b00000001) && (PIND & 0b00000010))
		{	
		PORTD = 0b01011100;
		}
	else
	{
		PORTD = 0x00;	
    }
		/*if((PINA==0b01011101))
		{
			PORTA = 0b01011100;
		}
		else
		{
			PORTA = 0x00;
		}*/
	}
	return 0;
}

