/*
 * QTR-8A.cpp
 *
 * Created: 12/20/2017 7:39:02 PM
 * Author : Sherlock
 */ 

#include <avr/io.h>
#include "uart.h"
#include "ADC.h"
#include <util/delay.h>

#define F_CPU 16000000UL


int main(void)
{
	uart0_init(UART_BAUD_SELECT(9600,F_CPU));

	 ADC_init();
		
	while (1)
	{	
		
 		ADC_setPin(4);
 		int ADC0_data = ADC_getValue();
 		uart0_puts("a:");
		uart0_putint(ADC0_data);
 		uart0_puts("\n \r");

 		ADC_setPin(5);
 		int ADC1_data = ADC_getValue();
		uart0_puts("b:");
 		uart0_putint(ADC1_data);
 		uart0_puts("\n \r");
 

// 		ADC_setPin(5);
// 		int ADC2_data = ADC_getValue();
// 		uart0_puts("c:");
// 		uart0_putint(ADC2_data);
//  		uart0_puts("\n \r");
 		_delay_ms(100);
 		
	}
}

