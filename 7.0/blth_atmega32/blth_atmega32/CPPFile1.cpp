/*
 * CPPFile1.cpp
 *
 * Created: 2/9/2018 8:36:19 PM
 *  Author: Sherlock
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define UART_rxBUFFER_SIZE 32
#define UART_txBUFFER_SIZE 32
#define UART_rxBUFFER  (UART_rxBUFFER_SIZE-1)
#define UART_txBUFFER  (UART_txBUFFER_SIZE-1)


volatile unsigned char rxBUFFER_QUEUE[UART_rxBUFFER];
volatile unsigned char txBUFFER_QUEUE[UART_rxBUFFER];
volatile unsigned char rxHEAD;
volatile unsigned char txHEAD;
volatile unsigned char rxTAIL;
volatile unsigned char txTAIL;

void uartInitialize(uint16_t baudRate);
void uartReceive();

class transmitClass
{

	private:


	public:
		void character();
		void string();
		void integer();

};

void uartInitialize(uint16_t baudRate){
	uint16_t uartBRR = (F_CPU/16/baudRate-1);
	
	// Set baud rate
	UBRRH = (unsigned char)(uartBRR>>8);
	UBRRL = (unsigned char)uartBRR;
	
	// Reciever and transmitter enable
	UCSRB = (1<<RXEN)|(1<TXEN);
	
	// Frame format: 8bitData, 2stopBit
	UCSRB
	
	
	
	
	
	transmitClass uartTransmit;

}





