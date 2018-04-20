/*
 * reciever.c
 *
 * Created: 11/22/2017 10:22:58 AM
 * Author : Prashant
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

uint16_t timer ;
long int p=0;
// unsigned char data= 0x00;
// long int sum =0 ;
// int i=0,freq;
int main(void)
{  
	
	DDRC = 0x00;
	DDRA = 0xFF;
   	sei();	
	TCCR1B = 0x01 ;
	TCNT1 = 0 ;
	GICR = (1<<INT0) ;
    while (1) 
    {
		for(int k=0;k<255;k++)
		{
			UART_transmit_ch(k);	
		_delay_ms(1000);
		}
		_delay_ms(100000);
// 		 if (timer > 40000)
// 		 {
// 			 PORTA =  0b00111000;
// 		 }
// 		 else
// 		 {
// 			 PORTA = 0b01110110;
// 		 }
    } 
	return 0; 
}

ISR (INT0_vect)
{
	timer = TCNT1;
	p++;
	TCNT1 = 0x00;
}
 