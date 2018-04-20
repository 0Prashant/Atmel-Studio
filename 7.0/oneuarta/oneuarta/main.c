/*
 * oneuarta.c
 *
 * Created: 23/10/2017 10:27:16 PM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0x02; 
	PORTB |= (1<<PINB0);
	UBRRH |= 0x00;
	UBRRL |= 25;
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<USBS) | (1<<UCSZ0) | (1<<UCSZ1);
	
    while (1) 
    {
		if (bit_is_clear(PINB , 0))
		{
			while(!(UCSRA & (1<< UDRE)))
			{	
			}
			PORTB |= (1<<PINB1);
			
			UDR = 0b11110000;
		}
		else
		{
			PORTB &= ~( 1 << PINB1);
		}
    }
	return 0;
}

