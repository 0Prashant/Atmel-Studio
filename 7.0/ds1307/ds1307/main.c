/*
 * ds1307.c
 *
 * Created: 11/14/2017 10:28:04 AM
 * Author : Prashant
 */ 
#define F_CPU 12000000UL
#include <avr/io.h>
#include <util/twi.h>
#define rs 0
#define rw 1
#define en 2
#include <util/delay.h>
#include <lcd.h>
#include <stdlib.h>
#include <avr/interrupt.h>

void i2c_initialize(int TWBR_value, unsigned char prescalar)
{
	TWCR = (1<<TWEN);
	TWSR = prescalar;
	TWBR = TWBR_value;
	
}

void i2c_start()
{
	TWCR = (1<<TWSTA) | (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void i2c_stop()
{
	TWCR = (1<<TWSTO) | (1<<TWINT) | (1<<TWEN);
}

void i2c_writedata(unsigned char wdata)
{
	TWDR = wdata;
	TWCR =  (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

unsigned char i2c_readdata(unsigned char ack)
{
	TWCR =  (1<<TWINT) | (1<<TWEN) | ack <<TWEA;
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}


void set_datetime(unsigned char y, unsigned char mo, unsigned char dt, unsigned char dy, unsigned char h, unsigned char mi, unsigned char s)
{
	i2c_start();
	i2c_writedata(0xD0);
	i2c_writedata(0x00);
	i2c_writedata(s);
	i2c_writedata(mi);
	i2c_writedata(h);	
	i2c_writedata(dy);
	i2c_writedata(dt);
	i2c_writedata(mo);
	i2c_writedata(y);
	i2c_stop();
}
void get_datetime(unsigned char *year, unsigned char *month, unsigned char *date, unsigned char *day, unsigned char *hour, unsigned char *minute, unsigned char *second)
{
	i2c_start();
	i2c_writedata(0xD0);
	i2c_writedata(0x00);
	i2c_stop();
	
	i2c_start();
	i2c_writedata(0xD1);
	*second = i2c_readdata(1);
	*minute = i2c_readdata(1);
	*hour = i2c_readdata(1);
	*day = i2c_readdata(1);
	*date = i2c_readdata(1);
	*month = i2c_readdata(1);
	*year = i2c_readdata(0);
	
	i2c_stop();
	
}

void init1307()
{
	i2c_initialize(52,0);
	i2c_start();
	i2c_writedata(0xD0);
	i2c_writedata(0x07);
	i2c_writedata(0x00);
	i2c_stop();
}

void send(unsigned char x)
{
	lcddata(('0'+(x>>4)));
	_delay_us(200);
	lcddata(('0'+(x & 0x0F)));
	
}
int main(void)
{
	init1307();
	lcdinitialise();
	unsigned char year,month,date,day,hour,minute,second;
	//char y[2], mo[2],d[2],h[2],mi[2],s[2];
	set_datetime(0x74,0x07,0x27,0x03,0x23,0x59,0x00);
	while (1) 
    {	
		get_datetime(&year, &month, &date, &day, &hour, &minute, &second);
		lcdgotoxy(2,1);
		lcdprint("Date:- ");
		lcdprint("20");
		send(year);
		lcdprint ("/");
		send(month);
		lcdprint ("/");
		send(date);
		lcdgotoxy(2,2);
		lcdprint("Time:- ");
		send(hour);
		lcdprint(":");
		send(minute);
		lcdprint(":");
		send(second);
    }
	return 0;
}
