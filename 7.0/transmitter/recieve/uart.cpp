
/**************************************************************************

Title  :  Interrupt UART library with receive/transmit circular buffers
Author :  Peter Fleury 
Edited :  Rishav 
          
DESCRIPTION:
    An interrupt is generated when the UART has finished transmitting or
    receiving a byte. The interrupt handling routines use circular buffers
    for buffering received and transmitted data.
    
    The UART_RX_BUFFER_SIZE and UART_TX_BUFFER_SIZE variables define
    the buffer size in bytes. Note that these variables must be a 
    power of 2.
    
USAGE:
    Referred to the header file uart.h for a description of the routines. 
   
*****************************************************************************/

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"




/* size of RX/TX buffers */
#define UART_RX_BUFFER_MASK ( UART_RX_BUFFER_SIZE - 1)
#define UART_TX_BUFFER_MASK ( UART_TX_BUFFER_SIZE - 1)

#if ( UART_RX_BUFFER_SIZE & UART_RX_BUFFER_MASK )
#error RX buffer size is not a power of 2
#endif
#if ( UART_TX_BUFFER_SIZE & UART_TX_BUFFER_MASK )
#error TX buffer size is not a power of 2
#endif



 #define UART_RECEIVE_INTERRUPT   USART_RXC_vect
 #define UART_TRANSMIT_INTERRUPT  USART_UDRE_vect
 #define UART_STATUS   UCSRA
 #define UART_CONTROL  UCSRB
 #define UART_DATA     UDR
 #define UART_UDRIE    UDRIE



/*
 *  module global variables
 */
static volatile unsigned char UART_TxBuf[UART_TX_BUFFER_SIZE];
static volatile unsigned char UART_RxBuf[UART_RX_BUFFER_SIZE];
static volatile unsigned char UART_TxHead;
static volatile unsigned char UART_TxTail;
static volatile unsigned char UART_RxHead;
static volatile unsigned char UART_RxTail;
static volatile unsigned char UART_LastRxError;



ISR(UART_RECEIVE_INTERRUPT)
/*************************************************************************
Function: UART Receive Complete interrupt
Purpose:  called when the UART has received a character
**************************************************************************/
{
    unsigned char tmphead;
    unsigned char data;
    unsigned char usr;
    unsigned char lastRxError;
 
 
    /* read UART status register and UART data register */ 
    usr  = UART_STATUS;
    data = UART_DATA;
    
    /* */

    lastRxError = (usr & (_BV(FE)|_BV(DOR)) );

        
    /* calculate buffer index */ 
    tmphead = ( UART_RxHead + 1) & UART_RX_BUFFER_MASK;
    
    if ( tmphead == UART_RxTail ) {
        /* error: receive buffer overflow */
        lastRxError = UART_BUFFER_OVERFLOW >> 8;
    }else{
        /* store new index */
        UART_RxHead = tmphead;
        /* store received data in buffer */
        UART_RxBuf[tmphead] = data;
    }
    UART_LastRxError = lastRxError;   
}

ISR(UART_TRANSMIT_INTERRUPT)
/*************************************************************************
Function: UART Data Register Empty interrupt
Purpose:  called when the UART is ready to transmit the next byte
**************************************************************************/
{
    unsigned char tmptail;

    
    if ( UART_TxHead != UART_TxTail) {
        /* calculate and store new buffer index */
        tmptail = (UART_TxTail + 1) & UART_TX_BUFFER_MASK;
        UART_TxTail = tmptail;
        /* get one byte from buffer and write it to UART */
        UART_DATA = UART_TxBuf[tmptail];  /* start transmission */
    }else{
        /* tx buffer empty, disable UDRE interrupt */
        UART_CONTROL &= ~_BV(UART_UDRIE);
    }
}


/*************************************************************************
Function: uart_init()
Purpose:  initialize UART and set baudrate
Input:    baudrate using macro UART_BAUD_SELECT()
Returns:  none
**************************************************************************/
void uart_init(unsigned int baudrate)
{
    UART_TxHead = 0;
    UART_TxTail = 0;
    UART_RxHead = 0;
    UART_RxTail = 0;
    
    /* Set baud rate */
    if ( baudrate & 0x8000 )
    {
    	 UART_STATUS = (1<<U2X);  //Enable 2x speed 
    	 baudrate &= ~0x8000;
    }
	
    UBRRH = (unsigned char)(baudrate>>8);
    UBRRL = (unsigned char) baudrate;
   
    /* Enable USART receiver and transmitter and receive complete interrupt */
    UART_CONTROL = _BV(RXCIE)|(1<<RXEN)|(1<<TXEN);
    
    /* Set frame format: asynchronous, 8data, no parity, 1stop bit */
    UCSRC = (1<<URSEL)|(3<<UCSZ0);
    UCSRC = (3<<UCSZ0);
  
}/* uart_init */


/*************************************************************************
Function: uart_getc()
Purpose:  return byte from ringbuffer  
Returns:  lower byte:  received byte from ringbuffer
          higher byte: last receive error
**************************************************************************/
unsigned int uart_getc(void)
{    
    unsigned char tmptail;
    unsigned char data;


    if ( UART_RxHead == UART_RxTail ) {
        return UART_NO_DATA;   /* no data available */
    }
    
    /* calculate /store buffer index */
    tmptail = (UART_RxTail + 1) & UART_RX_BUFFER_MASK;
    UART_RxTail = tmptail; 
    
    /* get data from receive buffer */
    data = UART_RxBuf[tmptail];
    
    return (UART_LastRxError << 8) + data;

}/* uart_getc */


/*************************************************************************
Function: uart_putc()
Purpose:  write byte to ringbuffer for transmitting via UART
Input:    byte to be transmitted
Returns:  none          
**************************************************************************/
void uart_putc(unsigned char data)
{
    unsigned char tmphead;

    
    tmphead  = (UART_TxHead + 1) & UART_TX_BUFFER_MASK;
    
    while ( tmphead == UART_TxTail ){
        ;/* wait for free space in buffer */
    }
    
    UART_TxBuf[tmphead] = data;
    UART_TxHead = tmphead;

    /* enable UDRE interrupt */
    UART_CONTROL    |= _BV(UART_UDRIE);

}/* uart_putc */


/*************************************************************************
Function: uart_puts()
Purpose:  transmit string to UART
Input:    string to be transmitted
Returns:  none          
**************************************************************************/
void uart_puts(const char *s )
{
    while (*s) 
      uart_putc(*s++);

}/* uart_puts */


/*************************************************************************
Function: uart_puts_p()
Purpose:  transmit string from program memory to UART
Input:    program memory string to be transmitted
Returns:  none
**************************************************************************/
void uart_puts_p(const char *progmem_s )
{
    register char c;
    
    while ( (c = pgm_read_byte(progmem_s++)) ) 
      uart_putc(c);

}/* uart_puts_p */



/*************************************************************************
Function: uart_available()
Purpose:  Determine the number of bytes waiting in the receive buffer
Input:    None
Returns:  Integer number of bytes in the receive buffer
**************************************************************************/
int uart_available(void)
{
        return (UART_RX_BUFFER_MASK + UART_RxHead - UART_RxTail) % UART_RX_BUFFER_MASK;
}/* uart_available */



/*************************************************************************
Function: uart_flush()
Purpose:  Flush bytes waiting the receive buffer.  Acutally ignores them.
Input:    None
Returns:  None
**************************************************************************/
void uart_flush(void)
{
        UART_RxHead = UART_RxTail;
}/* uart_flush */



/*************************************************************************
 Function: uart0_putint()
 Purpose:  transmit integer to UART0
 Input:    integer to be transmitted
 Returns:  none
 **************************************************************************/
void uart_putint(int input)
{
	char buffer[15];
	itoa(input,buffer,10);
	char * s = buffer;
	while (*s)
	uart_putc(*s++);

	}
	


