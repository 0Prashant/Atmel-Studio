/**
 * \file
 *
 * \brief USART basic driver.
 *
 *
 * Copyright (C) 2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 *
 */
#include <compiler.h>
#include <clock_config.h>
#include <usart_basic.h>
#include <atomic.h>

/* Static Variables holding the ringbuffer used in IRQ mode */
static uint8_t          USART_0_rxbuf[USART_0_RX_BUFFER_SIZE];
static volatile uint8_t USART_0_rx_head;
static volatile uint8_t USART_0_rx_tail;
static volatile uint8_t USART_0_rx_elements;
static uint8_t          USART_0_txbuf[USART_0_TX_BUFFER_SIZE];
static volatile uint8_t USART_0_tx_head;
static volatile uint8_t USART_0_tx_tail;
static volatile uint8_t USART_0_tx_elements;

void default_rx_isr(void);
void (*rx_isr_cb)(void) = &default_rx_isr;
void default_udre_isr(void);
void (*udre_isr_cb)(void) = &default_udre_isr;

void default_rx_isr(void)
{
	uint8_t data;
	uint8_t tmphead;

	/* Read the received data */
	data = UDR0;
	/* Calculate buffer index */
	tmphead = (USART_0_rx_head + 1) & USART_0_RX_BUFFER_MASK;
	/* Store new index */
	USART_0_rx_head = tmphead;

	if (tmphead == USART_0_rx_tail) {
		/* ERROR! Receive buffer overflow */
	}
	/* Store received data in buffer */
	USART_0_rxbuf[tmphead] = data;
	USART_0_rx_elements++;
}

void default_udre_isr(void)
{
	uint8_t tmptail;

	/* Check if all data is transmitted */
	if (USART_0_tx_elements != 0) {
		/* Calculate buffer index */
		tmptail = (USART_0_tx_tail + 1) & USART_0_TX_BUFFER_MASK;
		/* Store new index */
		USART_0_tx_tail = tmptail;
		/* Start transmission */
		UDR0 = USART_0_txbuf[tmptail];
		;
		USART_0_tx_elements--;
	}

	if (USART_0_tx_elements == 0) {
		/* Disable UDRE interrupt */
		UCSR0B &= ~(1 << UDRIE0);
	}
}

void USART_0_set_ISR_cb(usart_callback cb, usart_cb_t type)
{
	switch (type) {
	case RX_CB:
		rx_isr_cb = cb;
		break;
	case UDRE_CB:
		udre_isr_cb = cb;
		break;
	default:
		// do nothing
		break;
	}
}

/* Interrupt service routine for RX complete */
ISR(USART_RX_vect)
{
	(*rx_isr_cb)();
}

/* Interrupt service routine for Data Register Empty */
ISR(USART_UDRE_vect)
{
	(*udre_isr_cb)();
}

bool USART_0_is_tx_ready()
{
	return (USART_0_tx_elements != USART_0_TX_BUFFER_SIZE);
}

bool USART_0_is_rx_ready()
{
	return (USART_0_rx_elements != 0);
}

bool USART_0_is_tx_busy()
{
	return (!(UCSR0A & (1 << TXC0)));
}

uint8_t USART_0_read(void)
{
	uint8_t tmptail;

	/* Wait for incoming data */
	while (USART_0_rx_elements == 0)
		;
	/* Calculate buffer index */
	tmptail = (USART_0_rx_tail + 1) & USART_0_RX_BUFFER_MASK;
	/* Store new index */
	USART_0_rx_tail = tmptail;
	ENTER_CRITICAL(R);
	USART_0_rx_elements--;
	EXIT_CRITICAL(R);

	/* Return data */
	return USART_0_rxbuf[tmptail];
}

void USART_0_write(const uint8_t data)
{
	uint8_t tmphead;

	/* Calculate buffer index */
	tmphead = (USART_0_tx_head + 1) & USART_0_TX_BUFFER_MASK;
	/* Wait for free space in buffer */
	while (USART_0_tx_elements == USART_0_TX_BUFFER_SIZE)
		;
	/* Store data in buffer */
	USART_0_txbuf[tmphead] = data;
	/* Store new index */
	USART_0_tx_head = tmphead;
	ENTER_CRITICAL(W);
	USART_0_tx_elements++;
	EXIT_CRITICAL(W);
	/* Enable UDRE interrupt */
	UCSR0B |= (1 << UDRIE0);
}

int8_t USART_0_init()
{

	// Module is in UART mode

	/* Enable USART0 */
	PRR &= ~(1 << PRUSART0);

#define BAUD 9600

#include <utils/setbaud.h>

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	UCSR0A = USE_2X << U2X0 /*  */
	         | 0 << MPCM0;  /* Multi-processor Communication Mode: disabled */

	UCSR0B = 1 << RXCIE0    /* RX Complete Interrupt Enable: enabled */
	         | 0 << UDRIE0  /* USART Data Register Empty Interupt Enable: disabled */
	         | 1 << RXEN0   /* Receiver Enable: enabled */
	         | 1 << TXEN0   /* Transmitter Enable: enabled */
	         | 0 << UCSZ02; /*  */

	// UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) /*  */
	//		 | (0 << UPM01) | (0 << UPM00) /* Disabled */
	//		 | 0 << USBS0 /* USART Stop Bit Select: disabled */
	//		 | (1 << UCSZ01) | (1 << UCSZ00); /* 8-bit */

	uint8_t x;

	/* Initialize ringbuffers */
	x = 0;

	USART_0_rx_tail     = x;
	USART_0_rx_head     = x;
	USART_0_rx_elements = x;
	USART_0_tx_tail     = x;
	USART_0_tx_head     = x;
	USART_0_tx_elements = x;

	return 0;
}

void USART_0_enable()
{
	UCSR0B |= ((1 << TXEN0) | (1 << RXEN0));
}

void USART_0_enable_rx()
{
	UCSR0B |= (1 << RXEN0);
}

void USART_0_enable_tx()
{
	UCSR0B |= (1 << TXEN0);
}

void USART_0_disable()
{
	UCSR0B &= ~((1 << TXEN0) | (1 << RXEN0));
}

uint8_t USART_0_get_data()
{
	return UDR0;
}
