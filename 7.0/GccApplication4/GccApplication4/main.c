
#define F_CPU 1000000
#include <avr/io.h>

int main(void)
{
	DDRD=0xFF;
	PORTB = 0b00000011;
	TCCR0=0x07;
	TCCR1B  = 0x06;
	TCNT1L = 0x00;
	TCNT0=0;
	while(1)
	{
		if(TCNT0>0)
		{
			PORTD=0xFF;	
			TCNT1L = 0x00;
		}
		if(TCNT1L > 0)
		{
			PORTD=0x00;
			TCNT0 = 0x00;
		}
		
	}
	return 0;
}