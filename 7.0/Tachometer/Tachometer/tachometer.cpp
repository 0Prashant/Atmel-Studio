#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "tachometer.h"

volatile uint16_t count=0; // Pulse counter
volatile uint16_t rpm=0;   // Revolution per minute
volatile uint16_t rps=0;   // Revolution per seconds

void init_tachometer(void){
	
	 uart_init(UART_BAUD_SELECT(9600,F_CPU));
	
	TCCR1B |= (1<<WGM12);          // CTC mode
	TCCR1B |= (1<<CS12)|(1<<CS10); // Timer Clock = 1/1024 of sys 	
	
	// Initialize INT0
	MCUCR  |= (1<<ISC01);                    // Falling edge on INT0 triggers interrupt.
    GICR   |= (1<<INT0);                     // Enable INT0 interrupt
    TIMSK  |= (1<<OCIE1A);                   // Output compare 1A interrupt enable
	OCR1A   = (15624*SAMPLE_TIME);          // Compare value ~ 1 second	:(15624*SAMPLE_TIME)/1000
	
	sei();
}

ISR(TIMER1_COMPA_vect){      // Every SAMPLE_TIME!
	
	rps   = count/(PPR*SAMPLE_TIME); //count/(PPR*SAMPLE_TIME)
	rpm   = (rps*60);
	
	uart_putint(rps);
	uart_puts("\r") ;
	
	count = 0; 
}

ISR(INT0_vect){              // INT0 on falling edge
	count++;
}
