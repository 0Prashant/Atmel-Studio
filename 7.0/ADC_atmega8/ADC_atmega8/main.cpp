/*
 * ADC_atmega8.cpp
 *
 * Created: 11/13/2017 5:17:31 PM
 * Author : Sherlock
 */ 

#include <avr/io.h>
#include "uart.h"
#include "ADC.h"

#define F_CPU 16000000UL


int main(void)
{   
	uart0_init(UART_BAUD_SELECT(9600,F_CPU));
        ADC_init();
	ADC_setPin(1);

    while (1) 
    {
		int data = ADC_getValue();
		uart0_putint(data);
		uart0_puts("\n \r");
    }
}

