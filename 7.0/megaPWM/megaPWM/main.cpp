/*
 * megaPWM.cpp
 *
 * Created: 10/1/2017 8:08:28 PM
 * Author : Rishav Dhungel
 */ 

#include <avr/io.h>
#include "pwm.h"

#define F_CPU 16000000UL


int main(void)
{

	
	init_timer(1,0,0,0);
	selectPin_timer1(1,1,0);
	selectPin_timer3(0,0,0);
 	selectPin_timer4(0,0,0);
 	selectPin_timer5(0,0,0);
	 while (1) {}
		 
}
