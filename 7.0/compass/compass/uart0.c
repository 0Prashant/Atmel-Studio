/*
 * uart0.c
 *
 * Created: 9/19/2017 3:59:22 AM
 *  Author: n-is
 */

#include "uart0.h"
#include <avr/interrupt.h>

int8_t UART0_init(uint16_t baud_rate){
	uint16_t ubrr = (uint16_t)UBR0(baud_rate);
	/* Configure this later */
	//PRR0 &= ~(1 << PRUSART0);		// Enabling USART0

	/* -*- Setting Baud Rate -*- */
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t) ubrr;

	UCSR0B |= (0 << RXCIE0)
			| (0 << TXCIE0)
			| (0 << UDRIE0)
			| (1 << RXEN0)
			| (1 << TXEN0)
			| (0 << UCSZ02);

	UCSR0C |= (0 << UMSEL01) | (0 << UMSEL00)
			| (0 << UPM01) | (0 << UPM00)
			| (0 << USBS0)
			| (1 << UCSZ01) | (1 << UCSZ00);

	return 0;
}

/* -*- Polling Method -*- */
 void UART0_write(const uint8_t data){
	 while(!(UCSR0A & (1 << UDRE0)))
	 ;
	 UDR0 = data;
	 ;
 }

 uint8_t UART0_read( void ){
	 while(!(UCSR0A & (1 << RXC0)))
	 ;
	 return UDR0;
 }
 void UART0_writes(const char *str){
	 while(*str){
		 UART0_write(*str++);
	 }
 }

/* -*- Interrupt Method -*- */
//volatile static uint8_t tx_head;
//volatile static uint8_t tx_tail;
//volatile static uint8_t tx_buf[TX0_BUF_SIZE];
//volatile static uint8_t tx_elements;
//volatile uint8_t tail;
//
//void UART0_write(const uint8_t data){
	//uint8_t head;
	//head = (tx_head + 1) & (TX0_BUF_SIZE - 1);
	//while(tx_elements == TX0_BUF_SIZE)
		//;
	//tx_buf[head] = data;
	//tx_head = head;
	//++tx_elements;
	//UCSR0B |= (1 << UDRIE0);
//}
//
//ISR(USART_UDRE_vect){
	//if(tx_elements){
		//tail = (tx_tail + 1) & (TX0_BUF_SIZE - 1);
		//UDR0 = tx_buf[tail];
		//;
		//tx_tail = tail;
		//--tx_elements;
	//}
	//if(!tx_elements){
		//UCSR0B &= ~(1 << UDRIE0);
	//}
//}
//
//volatile static uint8_t rx_head;
//volatile static uint8_t rx_tail;
//volatile static uint8_t rx_buf[RX0_BUF_SIZE];
//volatile static uint8_t rx_elements;
//volatile uint8_t head, data;
//
//uint8_t UART0_read( void ){
	//uint8_t tail;
	//if(rx_elements){
		//tail = (rx_tail + 1) & (RX0_BUF_SIZE - 1);
		//rx_tail = tail;
		//--rx_elements;
		//return rx_buf[tail];
	//}
	//return 0;
//}
//
//ISR(USART_RX_vect){
	//data = UDR0;
	//head = (rx_head + 1) & (RX0_BUF_SIZE - 1);
	//rx_head = head;
	//if(head == rx_tail){
		///* Buffer Overflow */
		//// sei();
		//// UART0_writes("\n\r\n\rReceive Buffer Overflow\n\r\n\r");
	//}
	//rx_buf[head] = data;
	//++rx_elements;
//}

/* Other Basic Functions */

