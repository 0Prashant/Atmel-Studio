/*
 * motor_encoder.cpp
 *
 * Created: 12/14/2017 5:09:10 PM
 * Author : Prashant
 */ 
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include<avr/interrupt.h>
#include "lcd.h"
#define SAMPLE_TIME 0.2
#define ppr 100

volatile long int count=0, final = 0;
volatile int rpm;
volatile bool flag;
int main(void)
{
	lcd_init();
	sei();
	DDRA = 0xFF;
	DDRD = 0x00;
	TCCR1B |= 1<<WGM12 | 1<<CS12 | 1<< CS10; 
	TIMSK = 1<<OCIE1A;
	OCR1A = 15624*SAMPLE_TIME;
	GICR |= 1<<INT0;
	MCUCR |= 1<<ISC00 | 1<<ISC01;
	while (1) 
    {
		lcd_goto(0x00);
		rpm =(final*60)/( ppr * SAMPLE_TIME );
		lcd_puts("RPM- ");
		lcd_putint(rpm);
		lcd_goto(10);
		if (flag)
			lcd_puts("Ck  ");
		else
			lcd_puts("A.Ck");
		if(TCNT1>(14000/5))
			{
			lcd_goto(0x00);
			lcd_puts("RPM- 0  ");
			}	
    }
}
 
ISR(INT0_vect)
{
	count++;
	if (bit_is_set(PIND,0))
		flag = true;
	else
		flag = false;	
}

ISR(TIMER1_COMPA_vect)
{
	final = count;
	count = 0;
}

