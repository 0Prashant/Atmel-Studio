/*
 * ADC.cpp
 *
 * Created: 11/13/2017 5:13:37 PM
 * Author : Sherlock
 */

#include <avr/io.h>
#include "ADC.h"

void ADC_init(){

	ADMUX  |= (0<<REFS1)|(0<<REFS0);            // External reference voltage from AREF
	ADCSRA |= (1<<ADEN);                        // Enable ADC
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // Pre-scale 128

}

void ADC_setPin(uint8_t pin){
	ADMUX = (pin<<MUX0);						// Put the pin value to ADC Multiplexer Selection Register
	DDRC  = 0;
}

uint16_t ADC_getValue(void){

	ADCSRA |= (1<<ADSC);            // Start conversion
	while (!(ADCSRA & (1<<ADIF)));  // Waiting for conversion to complete
	
	ADCSRA |= (1<<ADIF);            // Clear ADIF flag for next conversion
	return ADC;

}