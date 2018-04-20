/*
 * 2560.cpp
 *
 * Created: 12/20/2017 2:24:22 PM
 * Author : Prashant
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define set_time 1359		//set value of time in milisecond

void work(void)				//work to be done after time is reached
{
	PORTA ^= 0xFF;
// 	TCCR1A = 0x00;									
// 	TCCR1B = 0x00;		// Uncomment these lines to run code only once	
// 	TCCR1C = 0x00;
// 	OCR1A = 0x00;						
// 	TIMSK1 = 0x00;
}

int main(void)
{
	sei();											//enable global interrupt
	TCCR1A = 0x00;									//setting ctc mode
	TCCR1B |= (1<<WGM12) | (1<<CS12);				//setting prescalar to 256
	TCCR1C |= 0x00;
	OCR1A = (int)(set_time * 7.8125);				//setting value of ocr 
	TIMSK1 |= (1<<OCIE1A);
	DDRA = 0xFF;
    while (1) 
    {
		
    }
	return 0;
}

ISR(TIMER1_COMPA_vect)
{
	work();
}
