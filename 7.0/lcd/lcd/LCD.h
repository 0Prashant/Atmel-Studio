#ifndef _LCD_H_
#define _LCD_H_

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


#endif