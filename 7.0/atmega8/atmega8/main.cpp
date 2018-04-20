/*
 * atmega8.cpp
 *
 * Created: 12/17/2017 12:10:21 PM
 * Author : Sherlock
 */ 

 #define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>




int main(void)
{
   
   DDRD = 0xff;
   DDRB = 0xff;
 
  
    
       while (1) 
    {

     PORTD = 0xff;
     PORTB = 0xff;
     _delay_ms(1);
     PORTD = 0;
     PORTB = 0;
       _delay_ms(1);
    }
    return 0;
}

