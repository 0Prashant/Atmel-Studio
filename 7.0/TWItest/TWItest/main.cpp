/*
 * TWItest.cpp
 *
 * Created: 10/24/2017 12:20:43 AM
 * Author : Rishav
 */ 

#define F_CPU 16000000UL // Clock Speed

#include <avr/io.h>

#include "HMC5883L.h"
#include "uart.h"
#include "TWI.h"


int main(void)
{
	
	
	HMC5883L_init();  
	uart0_init(UART_BAUD_SELECT(9600,F_CPU));
	uart0_puts("-----");
	
	while (1)
	{
		
		HMC5883L_read();		     
		
		uart0_putint(raw_x);
		uart0_puts("\t");
		uart0_putint(raw_y);
		uart0_puts("\t \n\r");
		
		
		
	}
}