/*
 * pwm.h
 *
 * Created: 10/1/2017 8:08:28 PM
 * Author : Rishav
 */ 

/**************************************************************
Available functions:
    init_timer(int timer1,int timer3,int timer4,int timer5);
		Timer initialization function
		MUST be called first to initialize either of 16 bits timer i.e. 1, 3, 4, 5
		Initializes to Phase Correct PWM mode and pre-scale 256 by default
    selectPin_timer1(int A1, int B1, int C1);
		Selects the pins among OC1A, OC1B and OC1C
		Configures respective pins as outputs
    selectPin_timer3(int A3, int B3, int C3);
		Selects the pins among OC3A, OC3B and OC3C
		Configures respective pins as outputs
    selectPin_timer4(int A4, int B4, int C4);
		Selects the pins among OC4A, OC4B and OC4C
		Configures respective pins as outputs
    selectPin_timer5(int A5, int B5, int C5);
		Select the pins among OC5A, OC5B and OC5C
		Configures respective pins as outputs

	Note:	
	-To change the frequency redefine the values freq(n)
	-To change pre-scaling change the configuration in each 
	function and redefine preScale(n) 
	-For constant value of duty cycle define the value in pwm.cpp (in percentage) 
	-To change duty cycle many times change the value of OCR in main program.
		
	
 *************************************************************/

#ifndef PWM_H_
#define PWM_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif






void init_timer(int timer1,int timer3,int timer4,int timer5);
void selectPin_timer1(int A1, int B1, int C1);
void selectPin_timer3(int A3, int B3, int C3);
void selectPin_timer4(int A4, int B4, int C4);
void selectPin_timer5(int A5, int B5, int C5);

#endif /*PWM_H_*/