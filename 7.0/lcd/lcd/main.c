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
#include <LCD.h>
int main(void)
{
	lcdinitialise();
    lcdprint("HELLO");
	while (1) 
    {
		
    }
	return 0;
}

