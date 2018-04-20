/*
 * testMegaPWM.cpp
 *
 * Created: 1/20/2018 6:43:15 PM
 * Author : Sherlock
 */

#define F_CPU 16000000UL
#include <avr/io.h>

 uint8_t dutyCycle1A = 75 ;
//  uint8_t dutyCycle1B = 25;
//  uint8_t dutyCycle1C = 10;

 uint16_t preScale1 = 256;
 uint16_t freq1 = 4000;

int main(void)
{


    DDRB   |= (1<<PINB5);

    /*Non -inverting Mode*/
    TCCR1A |= (1<<COM1A1)|(0<<COM1A0);

    // Prescale settings -- 256
    TCCR1B |= (1<<CS12)|(0<<CS11)|(0<<CS10);

    // Mode of operation -- Phase Correct Mode
    TCCR1A |= (1<<WGM11)|(0<<WGM10);
    TCCR1B |= (1<<WGM13)|(0<<WGM12);

    // Top value and update
    ICR1   = (F_CPU/(freq1*preScale1)-1);
    OCR1A  = (((F_CPU/(freq1*preScale1)-1)*dutyCycle1A)/100); /*Update value for OC1A*/
//     OCR1B = ((F_CPU/(freq1*preScale1)-1)*dutyCycle1B)/100; /*Update value for OC1B*/
//     OCR1C = ((F_CPU/(freq1*preScale1)-1)*dutyCycle1C)/100; /*Update value for OC1C*/


    while (1)
    {
    }
}

