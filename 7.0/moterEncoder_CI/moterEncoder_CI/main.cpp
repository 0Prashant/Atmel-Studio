/*
 * moterEncoder_CI.cpp
 *
 * Created: 10/7/2017 9:51:07 AM
 * Author : Rishav
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"

#define F_CPU 16000000UL
#define SAMPLE_TIME 0.1//In seconds *less than 4 seconds* 
#define kppr 200

volatile  long signed count=0; // Pulse counter
volatile  long signed rpm=0;   // Revolution per minute
volatile  float rpt=0;   // Revolution per sample time


int main(void)
{
	char a = 'q';
	
	
	DDRD   = (0<<PIND2)|(0<<PIND3)|(1<<PIND7);
	DDRC   = 0xff;
	PORTC |= (1<<PINC2);
    
	uart_init(UART_BAUD_SELECT(9600,F_CPU));

    // Timer Clock = 1/1024 of sys clock and CTC mode
    TCCR1B|=((1<<WGM12)|(1<<CS12)|(1<<CS10));
	
	// Initialize INT0
	MCUCR |= (1<<ISC00)|(1<<ISC01);   // Rising edge on INT0 triggers interrupt.
    GICR  |= (1<<INT0);               // Enable INT0 interrupt
    TIMSK |= (1<<OCIE1A);             // Output compare 1A interrupt enable
	OCR1A  = (15624*SAMPLE_TIME);     // Compare value = 1 second	
	sei();
	
	// Timer2 initialize
	TCCR2 |= (1<<CS22)|(1<<CS21)|(1<<CS20);
	
	// PWM
	TCCR2 |= (0<<WGM21)|(1<<WGM20); // Phase correct PWM
	TCCR2 |= (1<<COM21)|(1<<COM20);
	OCR2 = 63; 
	
	

	while(1)
	{
		while (uart_available()){
			a = uart_getc();
			uart_putc(a);
			uart_puts("\r");
		}
		
		if ( a =='F' || a =='f'){
			PORTC = (1<<PINC2)|(0<<PINC1)|(1<<PINC0);
			
		}
		else if (a == 'B' || a == 'b'){
			PORTC = (1<<PINC2)|(1<<PINC1)|(0<<PINC0);
		}

		
	}
return 0;
}

ISR(INT0_vect)
{
	    // INT0 on rising edge
	   if(!bit_is_set(PIND,3)){
           count--;   
		  }

	   else if(bit_is_set(PIND,3)){
		 count++;
         }
	
}

ISR(TIMER1_COMPA_vect)
{
	// Every SAMPLE_TIME sec !
	
	rpt   = (float)count/(kppr*SAMPLE_TIME);
	rpm   = (rpt*60);
			uart_putint(rpm);
			uart_puts("\r");
	count = 0; 
}

