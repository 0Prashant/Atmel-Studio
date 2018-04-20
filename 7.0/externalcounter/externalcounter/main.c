/*
 * externalcounter.c
 *
 * Created: 25/05/2017 12:27:14 PM
 * Author : Sushma
 */ 

#define F_CPU 1000000
#include <avr/io.h>
int main(void)
{
    PORTB = 0x01;
	DDRD = 0xFF;
	DDRC = 0xFF;
	TCCR0 = 0x07;
	TCCR1B = 0x05;
	TCNT0 = 0x00;
	unsigned char num[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00100111,0b01111111,0b01101111};
	while (1) 
    {
		for(unsigned char i=0;i<10;i++)
		{	
			PORTC = num[i];
			for(unsigned char j=0;j<10;j++)
			{
				TCNT1 = 0x0000;
				top:
				do
				{
					PORTD = num[j];
				}while(TCNT0<=0);
				if(TCNT1<800)
				{
					TCNT0 = 0x00;
					goto top;
				}
				TCNT0=0x00;
			}
		}
    }
	return 0;
}

