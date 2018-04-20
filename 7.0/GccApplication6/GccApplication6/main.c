/*
 * GccApplication6.c
 *
 * Created: 11/18/2017 3:14:09 PM
 * Author : Prashant
 */ 
#define F_CPU 1000000
#include <avr/io.h>

#include <util/delay.h>
int main(void)
{
	DDRA = 0b00000001;
   while(1) 
    {
		PORTA =0b00000010;
		PORTB =0b00000011;
		_delay_ms(1000);
    }
}

