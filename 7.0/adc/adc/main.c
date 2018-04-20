#define F_CPU 1000000
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define rs 0
#define rw 1
#define en 2
void lcdenable()
{
	PORTD |= 1<<en;
	asm volatile ("nop");
	asm volatile ("nop");
	PORTD &= ~(1<<en);
}
void lcdcheck()
{
	DDRB = 0x00;
	PORTD |= 1<<rw;
	PORTD &= ~(1<<rs);
	while(PORTC >= 0x80)
	{
		lcdenable();
	}
	DDRB = 0xFF;
}
void lcdcommand(unsigned char comd)
{
	lcdcheck();
	PORTD &= ~(1 << rs);
	PORTD &= ~(1<< rw);
	PORTB = comd & 0xF0;
	lcdenable();
	_delay_us(100);
	PORTB = comd <<4;
	lcdenable();
	_delay_ms(10);
	PORTB = 0;
}
void lcddata(unsigned char dat)
{
	lcdcheck();
	PORTD &= ~(1<< rw);
	PORTD |= 1 << rs;
	PORTB = dat & 0xF0;
	lcdenable();
	_delay_us(100);
	PORTB = dat<<4;
	lcdenable();
	_delay_ms(10);
	PORTB = 0;
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
int main(void)
{	
	lcdinitialise();
	DDRD = 0xFF;
	DDRB = 0xFF;
	sei();
	ADMUX |= 1<<ADLAR;
	ADMUX |= 1<<REFS0;
	ADCSRA |= 1<<ADIE;
	ADCSRA |= 1<<ADEN;
//	ADCSRA |= 0b00000011;
	ADMUX |= 1<<MUX0;
	ADCSRA |= 1<< ADSC;
    while (1) 
    {
    }
	return 0;
}
ISR (ADC_vect)
{
	lcdcommand(0x01);
	char result[4];
	itoa(ADCH, result,10);
	lcdprint(result);
	ADCSRA |=1<<ADSC;
	_delay_ms(200);
	
}

