/*
 * array.c
 *
 * Created: 22/05/2017 6:42:18 PM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
    while (1) 
    {
		unsigned char a=0xA4, temp;
		temp=a;
		for(unsigned char i=0 ; i<10 ; i++)	
		{
			if (temp & 0x01)
				PORTD = 0b00000001;
				
			else
				PORTD = 0x00;	
			temp = temp >> 1;
			_delay_ms(1000);	
		}
    }
	return 0;
}

