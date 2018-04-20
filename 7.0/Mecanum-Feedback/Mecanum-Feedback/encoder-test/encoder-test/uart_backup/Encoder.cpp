/* 
* Encoder.cpp
*
* Created: 10/15/2017 5:57:05 PM
* Author: Subash Timilsina
*/


#include "Encoder.h"

void Encoder::Initialise()
{
	INPUT(ENCODER_CHANNELA);
	INPUT(ENCODER_CHANNELB);
	SET(ENCODER_CHANNELA);
	SET(ENCODER_CHANNELB);
	Init_Interrupts();
	Init_Timers();
}

void Encoder::Init_Interrupts()
{
	sei();
	EIMSK &= ~(1<<ENCODER_INT);
	EICRA |= (1<<INT_ISC1);	//falling edge
	EIMSK |= (1<<ENCODER_INT);		//setting INT pin		
	EIFR |= (1<<INT_INTF);	    //clear int flag
}

void Encoder::Init_Timers()
{
	TCCR1B |= ((1<<WGM12)|(1<<CS30)|(1<<CS31)); //CTC mode and prescaler of 64
	TIMSK1 |= (1<<OCIE1A);
	OCR1A  = (F_CPU/1000)*(DELAYTIMEMS/64.0);
	TCNT1 = 0;
}