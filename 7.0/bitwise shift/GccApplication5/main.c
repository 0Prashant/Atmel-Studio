/*
 * GccApplication5.c
 *
 * Created: 22/05/2017 7:53:37 AM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD = 0xFF;
	PORTD = 0x01;
	_delay_ms(1000);
    while (1) 
    {
		PORTD = PORTD << 1;
		_delay_ms(1000);

		if (PORTD >=0x20)
		{
			PORTD = 0x01;
			_delay_ms(1000);
		}
    }
	return 0;
}

