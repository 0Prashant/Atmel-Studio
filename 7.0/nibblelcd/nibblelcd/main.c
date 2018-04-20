/*
 * lcd.c
 *
 * Created: 31/05/2017 9:28:24 AM
 * Author : Sushma
 */ 
#define F_CPU 1000000
#include <avr/io.h>
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
	DDRA = 0x00;
	PORTD |= 1<<rw;
	PORTD &= ~(1<<rs);
	while(PORTA >= 0x80)
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
	_delay_us(60);
	PORTA = comd <<4;
	lcdenable();
	PORTA = 0;
	_delay_ms(10);

}
void lcddata(unsigned char dat)
{
	lcdcheck();
	PORTD &= ~(1<< rw);
	PORTD |= 1 << rs; 
	PORTA = dat & 0xF0;
	lcdenable();
		//_delay_us(60);
	PORTA = dat<<4;
	lcdenable();
	PORTA = 0;	
	//_delay_ms(10);
}
void lcdinitialise()
{
	DDRD |= 1<<rs |1<<rw |1<<en ;
	_delay_ms(19);
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
	lcdcommand(0x06);
	_delay_ms(50);
}
void lcdprint(char *string)
{
	unsigned char i=0;
	while(string[i] != 0)
	{
		_delay_ms(3);
		lcddata(string[i]);
		i++;
	}
}
/*void lcdgotoxy(unsigned char x, unsigned char y)
{
	unsigned char address[4] = {0x80,0xC0,0x94,0xD4};
		if((x<1 && x>20) && (y<1 && y>4))
			{
				x=1;
				y=1;
			}
		lcdcommand((address[y-1]+x-1));	
}
void design1()
{
			unsigned char p,q;
			q=1;
			for(p=1;p<17;p++)
			{
				lcdgotoxy(p,q);
				lcdprint ("HELLO");
				_delay_ms(200);
				lcdcommand(0x01);
				_delay_ms(15);
			}
			q=2;
			lcdgotoxy(16,q);
			lcdprint ("HELLO");
			_delay_ms(200);
			lcdcommand(0x01);
			_delay_ms(15);
			q=3;
			lcdgotoxy(16,q);
			lcdprint ("HELLO");
			_delay_ms(200);
			lcdcommand(0x01);
			_delay_ms(15);
			q=4;
			for(p=16;p>0;p--)
			{
				lcdgotoxy(p,q);
				lcdprint ("HELLO");
				_delay_ms(200);
				lcdcommand(0x01);
				_delay_ms(15);
			}
				q=3;
				lcdgotoxy(1,q);
				lcdprint ("HELLO");
				_delay_ms(200);
				lcdcommand(0x01);
				_delay_ms(15);
				q=2;
				lcdgotoxy(1,q);
				lcdprint ("HELLO");
				_delay_ms(200);
				lcdcommand(0x01);
				_delay_ms(15);	
			q=1;
}*/
int main(void)
{
	lcdinitialise();
   /* lcdgotoxy(6,1);
    lcdprint("HELLO");
	lcdgotoxy(6,2);
	lcdprint("HELLO");
	lcdgotoxy(6,3);
	lcdprint("HELLO");
	lcdgotoxy(6,4);
	lcdprint("HELLO");*/
    lcdprint(" HELLO");
	while (1) 
    {
		
    }
	return 0;
}

