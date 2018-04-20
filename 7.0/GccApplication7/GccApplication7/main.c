/*
 * GccApplication7.c
 *
 * Created: 11/18/2017 3:41:56 PM
 * Author : Prashant
 */ 
#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char A[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
   DDRA = 0x01 ;
    while (1) 
    {
	for(int i=0;i<=10;i++)	
	{
		PORTA =	A[i];
		_delay_ms(500);
 
    }
}
	}

