/*
 * UART.h
 *
 * Created: 2/10/2018 2:30:59 AM
 *  Author: Sherlock
 */

#ifndef UART_H_
#define UART_H_

#ifndef F_CPU
 #define F_CPU 16000000UL
#endif

#define baudRate 9600
#define uartBRR ((F_CPU/16/baudRate)-1)


//Byte adds to tail when written and decreases from head when read
#define UART_BUFFER_SIZE 60
#define BufferSize  (UART_BUFFER_SIZE-1)

void uartInitialize();
void uartTransmitChar(unsigned char character);  	      // Puts a byte to ring buffer for transmisson
void uartTransmitString(char *string);
void uartTransmitInteger(int integer);
unsigned char uartReceiveChar();                              // Returns recieved byte from ring buffer

#endif /* UART_H_ */