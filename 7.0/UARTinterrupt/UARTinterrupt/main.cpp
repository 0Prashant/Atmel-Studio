/*
 * UARTinterrupt.cpp
 *
 * Created: 2/9/2018 11:08:21 PM
 * Author : Sherlock
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "UART.h"


int main (void)
{	
	uartInitialize();
	uartTransmitChar('a');
					  
	while (1)
	{
		uartTransmitChar(uartReceiveChar());	
	}
}

