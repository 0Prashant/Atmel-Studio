/*
 * Encoder_count.cpp
 *
 * Created: 11/17/2017 12:49:37 PM
 * Author : Rishav
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "uart.h"


#define F_CPU 16000000UL

char a;
volatile  long signed count=0; // Pulse counter


int main(void)
{
	 
	DDRD   = (0<<PIND2)|(0<<PIND3);
	
	
	uart_init(UART_BAUD_SELECT(9600,F_CPU));

	// Timer Clock = 1/1024 of sys clock and CTC mode
	TCCR1B|=((1<<WGM12)|(1<<CS12)|(1<<CS10));
	
	// Initialize INT0
	MCUCR |= (1<<ISC00)|(1<<ISC01);  
	GICR  |= (1<<INT0);               // Enable INT0 interrupt
	sei();
	
	while(1)
	{
		uart_putint (count);
		uart_puts("\n \r");
	}
}

ISR(INT0_vect){
	
       if (!bit_is_set(PIND,3))
       {
	count-- ;
       }
       else if (bit_is_set(PIND,3))
       {
	count++ ;
       }
	
}



