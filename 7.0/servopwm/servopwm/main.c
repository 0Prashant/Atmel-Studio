/*
 * servopwm.c
 *
 * Created: 16/10/2017 8:20:29 PM
 * Author : Sushma
 */ 

#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRD |= 0xFF;
	PORTD |= 0b00000001;
	TCCR1A |= 1<<COM1A1 | 1<<WGM11;
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = 19999;
	int i;
	while (1)
	{
		for(i=0;i<=1000;)
		{
			OCR1A = 1000+i;
			_delay_ms(1000);
			i+=1000/60;
			if (i>=1000)
			{
				i=0;
			}
		}
	}
	return 0;
}
