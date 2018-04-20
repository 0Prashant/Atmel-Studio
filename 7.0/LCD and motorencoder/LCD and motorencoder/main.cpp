/*
 * LCD and motorencoder.cpp
 *
 * Created: 10/12/2017 1:46:39 PM
 * Author : Sampada
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"

#define F_CPU 16000000UL
#define PPR 1024
#define BAUD_RATE 9600
#define PI 3.1416
volatile uint16_t count = 0;
volatile float dist_diff =0;
uint8_t dist_dig = 0;
volatile long signed countperSec = 0;
volatile float revperMin = 0;
volatile float revperSec = 0;
volatile float distance = 0;
volatile float  revolution = 0;
volatile long signed i =0;

ISR (INT0_vect){
	
	count ++;
	//if (count % 24==0){
		//revolution ++;
	//}
    revolution = count/24;
	lcd_gotoxy(5,1);
	lcd_putint(revolution);
	
	
	distance =(float)(revolution * 2* PI * 2.8);
	dist_diff = distance - (int)distance;
	dist_dig = dist_diff * 100;
	lcd_gotoxy(13,2);
	lcd_putch('.');
	lcd_gotoxy(14,2);
	lcd_putint(dist_dig);
	
	lcd_gotoxy(7,2);
	lcd_putint(distance);
}
/*ISR (TIMER1_COMPA_vect){
	countperSec =count;
	revperSec = count/PPR;
	revperMin = revperSec*60;
	lcd_gotoxy(7,1);
	lcd_puts("RPM:");
	lcd_putint(revperMin);
	count = 0;
}*/


int main(void)
{
 lcd_init();
 sei();
 DDRD|= (0<<INT0)|(1<<PIND7);
 TCCR1B|=(1<<CS12)|(1<<CS10);
 TCCR1B|=(1<<WGM12);
 //TIMSK|=(1<<OCIE1B);
 OCR1A = 15625;
 MCUCR|= (1<<ISC00)|(1<<ISC01);
 GICR|= (1<<INT0);
 lcd_gotoxy(2,1);
lcd_puts("Rn:");
 lcd_gotoxy(2,2);
 lcd_puts("Dis:");
    while (1) 
    {
    }
}





























































































































































































































