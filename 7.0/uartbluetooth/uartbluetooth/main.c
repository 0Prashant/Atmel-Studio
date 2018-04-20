/*
 * uartbluetooth.c
 *
 * Created: 11/10/2017 8:23:12 PM
 * Author : Prashant
 */ 
#define F_CPU 11059200UL
#include <avr/io.h>
#include <util/delay.h>
#include <UART.h>
#include <avr/interrupt.h>

int main(void)
{
	sei();
	GICR = 1 << INT0;
	DDRA |= 0xFF;
	DDRC |= (1 << PINC0) | (1<<PINC1) ;
	UART_initialize(9600, 8, 1,1,0);
	while (1)
	{		
	}
	return 0;
}

void send_data_to_led(unsigned char d)
{
	for(int i=0;i<8;i++)
	{
		PORTC = (0x01) & (d>>(8-i));
		_delay_ms(10);
	}
}

ISR(USART_RXC_vect)
	{
		int a;
		a = UDR;
		UART_transmit_character(a);
		if (a==0)
			send_data_to_led(0b00111111);
		if (a==1)
			send_data_to_led(0b00000110);
		if (a==2)
			send_data_to_led(0b01011011);
		if (a==3)
			send_data_to_led(0b01001111);
		if (a==4)
			send_data_to_led(0b01100110);
		if (a==5)
			send_data_to_led(0b01101101);
		if (a==6)
			send_data_to_led(0b01111101);
		if (a==7)
			send_data_to_led(0b00000111);
		if (a==8)
			send_data_to_led(0b01111111);
		if (a==9)
			send_data_to_led(0b01101111);	
		_delay_ms(2000);	
	}


