/*
 * UART.cpp
 *
 * Created: 2/9/2018 11:08:49 PM
 * Author: Sherlock
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


#include "UART.h"

volatile unsigned char rxRingBuffer[BufferSize];
volatile unsigned char txRingBuffer[BufferSize];

volatile uint8_t rxHead = 0;
volatile uint8_t txHead = 0;
volatile uint8_t rxTail = 0;
volatile uint8_t txTail = 0;

void uartInitialize(){


	// Set baud rate
	UBRR0H = (unsigned char)(uartBRR>>8);
	UBRR0L = (unsigned char)uartBRR;

	//Reciever, transmitter and UART recieve complete interrupt enable
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);

	// Set frame format: 8data, 2stop bit
	UCSR0C = /*(1<<URSEL)|*/(1<<USBS0)|(3<<UCSZ00);

	//Global interrupt enable
	sei();
}


unsigned char uartReceiveChar()
{
	unsigned char rxCharacter=0;

	// If no data in buffer
	if (rxHead==rxTail) return 0;

	// Read data from rxBuffer and advance the head (Free space created)
	rxCharacter = rxRingBuffer[rxHead];
	rxHead = (rxHead+1)%BufferSize;

	return rxCharacter;
}

void uartTransmitChar(unsigned char character){

	//Wait for buffer to have a empty space
	while (((txHead == (txTail+1)%BufferSize)));

	//A byte written to txBuffer and tail advanced  (Free space decreased)
	txRingBuffer[txTail] = character;
	txTail = (txTail+1)%BufferSize;

	//Enable UartDataRegisterEmpty interrupt
	UCSR0B |= (1<<UDRIE0);
}

void uartTransmitInteger(int integer)
{
	char intBuffer[15];
	itoa(integer,intBuffer,10);
	char *s = intBuffer;

	while (*s)
		uartTransmitChar(*s++);

}



void uartTransmitFloat(float number){
	
	int tempInteger, temp2Integer;
	float diffValue;
	
	 tempInteger = (int)number;
	 diffValue = number - (float)tempInteger;
	 temp2Integer = (int)(diffValue*1000.0);
	
	uartTransmitInteger(tempInteger);
	uartTransmitChar('.');
	uartTransmitInteger(temp2Integer);

}


ISR(USART_RX_vect)  // Code to be executed when a byte is recieved
{
	//Read a byte from UDR and written to rxRingBuffer
	rxRingBuffer[rxTail] = UDR0;
	rxTail = (rxTail+1)%BufferSize;
}

ISR(USART_UDRE_vect) //Code to be executed when ready to transmit the next byte
{

	//When ring buffer has some data
	if (txHead != txTail)
	{
		// A byte written to UDR from txRingBuffer and txHead pointed to next byte
		UDR0 = txRingBuffer[txHead];
		txRingBuffer[txHead]=0;
		txHead = (txHead+1)%BufferSize;
	}

	else UCSR0B &= ~(1<<UDRIE0); //Empty txBuffer, disable UDRE interrupt

}
