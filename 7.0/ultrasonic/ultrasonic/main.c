/*
 * ultrasonic.c
 *
 * Created: 22/06/2017 5:27:17 PM
 * Author : Sushma
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <math.h>
#define rs 0
#define rw 1
#define en 3
#define echo 2
#define trigger 4
unsigned  char i;
long int value;
void lcdenable()
{
	PORTD |= 1<<en;
	asm volatile ("nop");
	asm volatile ("nop");
	PORTD &= ~(1<<en);
}
void lcdcheck()
{
	DDRA = 0x00;
	PORTD |= 1<<rw;
	PORTD &= ~(1<<rs);
	while(PORTD >= 0x80)
	{
	  lcdenable();
	}
	DDRA = 0xFF;
}
void lcdcommand(unsigned char comd)
{
	lcdcheck();
	PORTD &= ~(1 << rs);
	PORTD &= ~(1<< rw);
	PORTA = comd & 0xF0;
	lcdenable();
	_delay_us(100);
	PORTA = comd <<4;
	lcdenable();
	_delay_ms(10);
	PORTA = 0;
}
void lcddata(unsigned char dat)
{
	lcdcheck();
	PORTD &= ~(1<< rw);
	PORTD |= 1 << rs; 
	PORTA = dat & 0xF0;
	lcdenable();
		_delay_us(100);
	PORTA = dat<<4;
	lcdenable();
	_delay_ms(10);
	PORTA = 0;
}
void lcdinitialise()
{
	DDRD |= 1<<rs |1<<rw |1<<en ;
	_delay_ms(15);
	lcdcommand(0x01);
	_delay_ms(2);
	lcdcommand(0x33);
	_delay_us(50);
	lcdcommand(0x32);
	_delay_us(50);
	lcdcommand(0x28);
	_delay_us(50);
	lcdcommand(0x0E);
	_delay_us(50);
}
void lcdprint(char *string)
{
	unsigned char i=0;
	while(string[i] != 0)
	{
		lcddata(string[i]);
		i++;
	}
}
void lcdgotoxy(unsigned char x, unsigned char y)
{
	unsigned char address[4] = {0x80,0xC0,0x94,0xD4};
		if((x<1 && x>20) && (y<1 && y>4))
			{
				x=1;
				y=1;
			}
		lcdcommand((address[y-1]+x-1));	
}
int main(void)
{
	i=1;
	DDRD |=1<<trigger;
	lcdinitialise();
	sei();
	long int final;
	GICR = 1<< INT0;
	MCUCR |= 1<< ISC00;
	float distance;
	char dis[5];
	TCCR1B = 0x01;
	PORTD &= ~(1<<echo);
	DDRD &= ~(1<<echo);
	lcdprint ("Distance = ");
	while (1) 
    {
		PORTD |= 1<<trigger;
		_delay_us(12);
		PORTD &= ~(1<<trigger);
		DDRD &= ~(1<<echo);
		distance = value / 58 ;
		value = abs(distance);
		final = value;
		itoa(final,dis,10);
		lcdgotoxy(12,1);
		lcdprint(dis);
	} 
	return 0;
}
ISR (INT0_vect)
{
	if (i==1)
	{
		TCCR1B = 0x01;
		TCNT1 = 0;
		i=0;
	}
	else
	{
		value = TCNT1;
		TCCR1B = 0x00;
		TCNT1 = 0;
		i=1;
	}
}




