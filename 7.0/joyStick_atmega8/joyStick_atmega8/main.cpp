 /*
  * joyStick_atmega8.cpp
  *
  * Created: 11/13/2017 1:30:57 AM
  * Author : Sherlock
  */


 #include <avr/io.h>
 #include "uart.h"
 #include "ADC.h"
 #define khello	uart0_puts 
 

 #define F_CPU 16000000UL

 uint16_t ADC0_data ;
 uint16_t ADC1_data ;
 uint16_t ADC2_data ;
 uint16_t ADC3_data ;
 uint16_t ADC4_data ;
 uint16_t ADC5_data ;
 uint16_t ADC6_data ;
 uint16_t ADC7_data ;

 int main(void)
 {
 	uart0_init(UART_BAUD_SELECT(9600,F_CPU));
 	ADC_init();

 	while (1)
 	{
 		ADC_setPin(0);
 		int ADC0_data = ADC_getValue();
    		uart0_putint(ADC0_data);
		uart0_puts("\n \r");

 		ADC_setPin(1);
 		int ADC1_data = ADC_getValue();
 		uart0_putint(ADC1_data);
 		khello("\n \r");


 		ADC_setPin(3);
 		int ADC2_data = ADC_getValue();
 		uart0_putint(ADC2_data);
 		uart0_puts("\n \r");

 		ADC_setPin(4);
 		int ADC3_data = ADC_getValue();
 		uart0_putint(ADC3_data);
 		uart0_puts("\n \r");

 	       uart0_puts("Hello man");
 	       uart0_putint(1123);
 	}
 }




