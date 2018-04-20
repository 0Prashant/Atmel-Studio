/*
 * uartbluetooth.c
 *
 * Created: 11/10/2017 8:23:12 PM
 * Author : Prashant
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void send_data_to_led(unsigned char d)
{
	for(int i=0;i<8;i++)
	{
		PORTC =(0x01 & (d >> (7-i))) | (1<<PINC7);
		if (bit_is_clear(PINC,7))
			_delay_ms(60);
		else
			_delay_ms(10);	
	}
}

int main(void)
{
	DDRC = 0x0F ;
	while (1)
	{		
		send_data_to_led(0b10101010);	
	}
	return 0;
}





