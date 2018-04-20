/*
 * GccApplication4.c
 *
 * Created: 21/05/2017 9:40:32 PM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
   DDRD = 0x7F;
   DDRC = 0x7F;
   char p,q,a,b;
   top:
   p=0,q=0,a=1,b=1;
   PORTD = 0x01;
   PORTC = 0x01;
    while(1)
	{
		if (bit_is_clear(PIND,7))
		{
			if(p==0)
			{
				p=1;
				PORTD |= PORTD << 1;
				a++;
				if(a>=8)
				{
					PORTC = 0x00;
					_delay_ms(3000);
					goto top;

				}
			}
		}
		else
			p=0;
	if (bit_is_clear(PINC,7))
	{
		if(q==0)
		{
			q=1;
			PORTC |= PORTC << 1;
			b++;
			if(b>=8)
			{
				PORTD = 0x00;
				_delay_ms(3000);
				goto top;
			}

		}
	}
	else
	q=0;		
	
		}
	return 0;
}

