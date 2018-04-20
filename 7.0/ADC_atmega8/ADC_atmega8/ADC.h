/*
 * ADC.h
 *
 * Created: 11/13/2017 5:10:30 PM
 * Author : Sherlock
 */

#ifndef ADC_H_
#define ADC_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

void ADC_init();
void ADC_setPin(uint8_t pin);
uint16_t ADC_getValue();


#endif /*ADC.h*/
