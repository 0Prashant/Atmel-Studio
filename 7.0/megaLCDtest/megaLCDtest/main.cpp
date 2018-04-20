/*
 * megaLCDtest.cpp
 *
 * Created: 1/6/2018 5:58:28 AM
 * Author : Sherlock
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
   int a = 10;
    lcd_init();	                  // Initialize the LCD
   // lcd_puts("Hi I am MrLCD !!");	  // Displays the character
  
    while (1)
    {
	 lcd_puts("Data=");
	 lcd_unum(a);
	_delay_ms(10);
	lcd_clear();
    }
}

