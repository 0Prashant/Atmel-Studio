/*
 * pwm.cpp
 *
 * Created: 10/1/2017 8:08:28 PM
 * Author : Rishav
 */

#include <avr/io.h>
#include "pwm.h"

#define F_CPU 16000000UL

 uint16_t freq1 = 4000;
 uint16_t freq3 = 100;
 uint16_t freq4 = 100;
 uint16_t freq5 = 100;

uint16_t preScale1 = 256;
uint16_t preScale3 = 256;
uint16_t preScale4 = 256;
uint16_t preScale5 = 256;

 uint8_t dutyCycle1A = 50 ;
 uint8_t dutyCycle1B = 75;
 uint8_t dutyCycle1C = 10;


 uint8_t dutyCycle3A = 90 ;
 uint8_t dutyCycle3B = 50 ;
 uint8_t dutyCycle3C = 10;


 uint8_t dutyCycle4A = 90 ;
 uint8_t dutyCycle4B = 50 ;
 uint8_t dutyCycle4C = 10;


 uint8_t dutyCycle5A = 90 ;
 uint8_t dutyCycle5B = 50 ;
 uint8_t dutyCycle5C = 10;

void init_timer(int timer1,int timer3,int timer4,int timer5){
	if (timer1 == 1)
	{

		// Prescale settings -- 256
		TCCR1B |= (1<<CS12)|(0<<CS11)|(0<<CS10);

		// Mode of operation -- Phase Correct Mode
		TCCR1A |= (1<<WGM11)|(0<<WGM10);
		TCCR1B |= (1<<WGM13)|(0<<WGM12);

		// Top value and update
		ICR1   = (F_CPU/(freq1*preScale1)-1);
		OCR1A = ((F_CPU/(freq1*preScale1)-1)*dutyCycle1A)/100; /*Update value for OC1A*/
		OCR1B = ((F_CPU/(freq1*preScale1)-1)*dutyCycle1B)/100; /*Update value for OC1B*/
		OCR1C = ((F_CPU/(freq1*preScale1)-1)*dutyCycle1C)/100; /*Update value for OC1C*/
	}

	if (timer3 == 1)
	{

		// Prescale settings -- 256
		TCCR3B |= (1<<CS32)|(0<<CS31)|(0<<CS30);

		// Mode of operation -- Phase Correct Mode
		TCCR3A |= (1<<WGM31)|(0<<WGM30);
		TCCR3B |= (1<<WGM33)|(0<<WGM32);

		// Top value and update
		ICR3   = (F_CPU/(freq3*preScale3)-1);
		OCR3A  = ((F_CPU/(freq3*preScale3)-1)*dutyCycle3A)/100; /*Update value for OC3A*/
		OCR3B  = ((F_CPU/(freq3*preScale3)-1)*dutyCycle3B)/100; /*Update value for OC3B*/
		OCR3C  = ((F_CPU/(freq3*preScale3)-1)*dutyCycle3C)/100; /*Update value for OC3C*/
	}

	if (timer4 == 1)
	{

		// Prescale settings -- 256
		TCCR4B |= (1<<CS42)|(0<<CS41)|(0<<CS40);

		// Mode of operation -- Phase Correct Mode
		TCCR4A |= (1<<WGM41)|(0<<WGM40);
		TCCR4B |= (1<<WGM43)|(0<<WGM42);

		// Top value and update
		ICR4   = (F_CPU/(freq3*preScale4)-1);
		OCR4A = ((F_CPU/(freq3*preScale4)-1)*dutyCycle4A)/100; /*Update value for OC4A*/
		OCR4B = ((F_CPU/(freq3*preScale4)-1)*dutyCycle4B)/100; /*Update value for OC4B*/
		OCR4C = ((F_CPU/(freq3*preScale4)-1)*dutyCycle4C)/100; /*Update value for OC4C*/
	}

	if (timer5 == 1)
	{

		// Prescale settings -- 256
		TCCR5B |= (1<<CS52)|(0<<CS51)|(0<<CS50);

		// Mode of operation -- Phase Correct Mode
		TCCR5A |= (1<<WGM51)|(0<<WGM50);
		TCCR5B |= (1<<WGM53)|(0<<WGM52);

		// Top value and update
		ICR5   = (F_CPU/(freq5*preScale5)-1);
		OCR5A = ((F_CPU/(freq3*preScale5)-1)*dutyCycle5A)/100; /*Update value for OC5A*/
		OCR5B = ((F_CPU/(freq3*preScale5)-1)*dutyCycle5B)/100; /*Update value for OC5B*/
		OCR5C = ((F_CPU/(freq3*preScale5)-1)*dutyCycle5C)/100; /*Update value for OC5C*/
	}

}


void selectPin_timer1(int A1, int B1, int C1){
	if(A1 == 1){
		DDRB   |= (1<<PINB5);
		TCCR1A |= (1<<COM1A1)|(0<<COM1A0); /*Non -inverting Mode*/}
	if(B1 == 1){
		DDRB   |= (1<<PINB6);
		TCCR1A |= (1<<COM1B1)|(0<<COM1B0); /*Non -inverting Mode*/}
	if(C1 == 1){
		DDRB   |= (1<<PINB7);
		TCCR1A |= (1<<COM1C1)|(0<<COM1C0); /*Non -inverting Mode*/}
}

void selectPin_timer3(int A3, int B3, int C3){
	if(A3 == 1){
		DDRE   |= (1<<PINE3);
	TCCR3A |= (1<<COM3A1)|(0<<COM3A0); /*Non -inverting Mode*/}
	if(B3 == 1){
		DDRE   |= (1<<PINE4);
	TCCR3A |= (1<<COM3B1)|(0<<COM3B0); /*Non -inverting Mode*/}
	if(C3 == 1){
		DDRE   |= (1<<PINE5);
	TCCR3A |= (1<<COM3C1)|(0<<COM3C0); /*Non -inverting Mode*/}
}

void selectPin_timer4(int A4, int B4, int C4){
	if(A4 == 1){
		DDRH   |= (1<<PINH3);
	TCCR4A |= (1<<COM4A1)|(0<<COM4A0); /*Non -inverting Mode*/}
	if(B4 == 1){
		DDRH   |= (1<<PINH4);
	TCCR4A |= (1<<COM4B1)|(0<<COM4B0); /*Non -inverting Mode*/}
	if(C4 == 1){
		DDRH   |= (1<<PINH5);
	TCCR4A |= (1<<COM4C1)|(0<<COM4C0); /*Non -inverting Mode*/}
}

void selectPin_timer5(int A5, int B5, int C5){
	if(A5 == 1){
		DDRL   |= (1<<PINL3);
	TCCR5A |= (1<<COM5A1)|(0<<COM5A0); /*Non -inverting Mode*/}
	if(B5 == 1){
		DDRL   |= (1<<PINL4);
	TCCR5A |= (1<<COM5B1)|(0<<COM5B0); /*Non -inverting Mode*/}
	if(C5 == 1){
		DDRL   |= (1<<PINL5);
	TCCR5A |= (1<<COM5C1)|(0<<COM5C0); /*Non -inverting Mode*/}
}







