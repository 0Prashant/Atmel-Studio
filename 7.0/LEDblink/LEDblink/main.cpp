/*
 * LEDblink.cpp
 *
 * Created: 1/18/2018 7:46:17 PM
 * Author : Sherlock
 */ 
 #define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{    DDRD = 0xff;
    /* Replace with your application code */
    while (1) 
    {
	    PORTD  = 0xff;
	    _delay_ms(1000);
	    PORTD = 0;
	    _delay_ms(1000);
	    
    }
}

