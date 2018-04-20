/*
 * oneuartb.c
 *
 * Created: 24/10/2017 8:19:45 PM
 * Author : Sushma
 */ 
 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0x01; 
	
	UBRRH |= 0x00;
	UBRRL |= 25;
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<USBS) | (1<<UCSZ0) | (1<<UCSZ1);
	
    while (1) 
    {
		
			while(!(UCSRA & (1<< RXC)))
			{	
			}
			if (UDR == 0xF0)
			PORTB ^= 1<<PINB0 ;
    }
	return 0;
}



