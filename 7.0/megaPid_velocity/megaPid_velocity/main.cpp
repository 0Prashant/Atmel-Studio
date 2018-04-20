/*
 * megaPid_velocity.cpp
 *
 * Created: 11/25/2017 12:30:32 PM
 * Author : Rishav
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define F_CPU 16000000UL
#define ksampleTime 0.02 // In seconds *less than 4 seconds
#define kppr 250        // Pulse per revolution

#define preScale3 1024
#define freq3 400

uint8_t dutyCycle3A = 90 ;

volatile long signed count = 0; // Pulse count
volatile long signed rpm = 0;	// Revolution per minutes
volatile float rpt = 0 ;	// Revolution per sample time

// Error terms
float integral_err ;
float previous_error ;

float kp, ki, kd ; // Proportional, integration and derivative gain constant initialization
uint16_t setPoint ;




void valueLimit(uint16_t currentValue, uint16_t maxValue, uint16_t minValue){
	
	if (currentValue >= maxValue){
		currentValue = maxValue;
	}
	
	if (currentValue <= minValue){
		currentValue = minValue;
	}
}


uint16_t pid(uint16_t currentValue) {


	float p_err = setPoint - currentValue  ;
	float i_err = integral_err  ; // Sum of velocity errors over time
	float d_err = p_err - previous_error ; // Rate of change of the error

	// Output terms calculation
	float p_term =  kp * p_err ; // Proportional component of output
	float i_term =  ki * i_err ; // Integral component of output
	float d_term =  kd * d_err ; // Derivative component of output

	float output ; // Sum of P, I and D terms

	// Output calculation
	output = p_term + i_term + d_term ;

	// Error summation and update
	previous_error = p_err ;
	integral_err += p_err ;

	return output ;
	                                                                                                                                                                                                                                         
}

void set_constant(float KP, float KI, float KD);


void in_kp(void){ kp += 0.01; }	  // Increase constant kp
void dr_kp(void){ kp -= 0.01; }	  // Decrease constant kp
void in_ki(void){ ki += 0.0001;}  // Increase constant ki
void dr_ki(void){ ki -= 0.0001;}  // Decrease constant ki
void in_kd(void){ kd += 0.05;}	  // Increase constant kd
void dr_kd(void){ kd -= 0.05;}	  // Decrease constant kd

int main(void)
{      
               uart0_init(UART_BAUD_SELECT(9600,F_CPU))	;  
   
	       // PB0 -> INT0
	       // PB1 -> INT1		
		DDRD = (0<<PD0) | (0<<PD1);

		// Timer clock = 1/1024 of system clock and CTC mode
		TCCR1B |= (1<<WGM12) | (1<<CS12) | (1<<CS10);

		// Initialize INT0
		EICRA  |=  (1<<ISC01) | (1<<ISC00); // Rising edge triggers interrupt
		EIMSK  |=  (1<<INT0);		   // Enable interrupt0
		TIMSK1 |= (1<<OCIE1A);		   // Output compare 1A interrupt enable
		OCR1A   = (15624*ksampleTime);	   // Compare value => 1 sec
		sei();	


		 DDRE   |= (1<<PINE3);
		 // Pre scale settings -- 256
		 TCCR3B |= (1<<CS32)|(0<<CS31)|(1<<CS30);
		 // Mode of operation -- Phase Correct Mode
		 TCCR3A |= (1<<WGM31)|(0<<WGM30);
		 TCCR3B |= (1<<WGM33)|(0<<WGM32);
		 // Top value and update
		  TCCR3A |= (1<<COM3A1)|(0<<COM3A0); /*Non -inverting Mode*/
// 		 ICR3 =  (F_CPU/(freq3*preScale3)-1);
// 		 OCR3A = ((F_CPU/(freq3*preScale3)-1)*dutyCycle3A)/100; /*Update value for OC3A*/
		 ICR3 = 38;
		 OCR3A = 20 ; // 38 is ICR
		

		

	while (1)
	{		 
	}
	return 0;
}

ISR (INT0_vect){
      
	// INT0 on rising edge
	if (!bit_is_set(PIND,1)){
		count--;
	}
	else if (bit_is_set(PIND,1)){
		count++;
	}					        
}

ISR(TIMER1_COMPA_vect){
	// Every SAMPLE_TIME sec !
	rpt = (float)count/(kppr*ksampleTime);
	rpm = (rpt*60);
		uart0_putint(rpm);
		uart0_puts("\n \r");
	count = 0;
}



