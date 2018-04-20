/*
 * PID_motorVelocity.cpp
 *
 * Created: 11/25/2017 3:36:35 AM
 * Author : Rishav
 */ 

#include <avr/io.h>



float kp, ki, kd ; // Proportional, integration and derivative gain constant initialization
 uint16_t setPoint ;


uint16_t pid(uint16_t currentValue) {

// Error terms 
float p_err = setPoint - currentValue  ;
float i_err  ; ; // Sum of velocity errors over time
float d_err ; // Rate of change of the error



// Output terms calculation
float p_term =  kp * p_err ; // Proportional component of output
float i_term =  ki * i_err ; // Integral component of output
float d_term =  kd * d_err ; // Derivative component of output

float output ; // Sum of P, I and D terms




// Output calculation
output = p_term + i_term + d_term ;

// Error summation and update
float previous_error = p_err ;
i_err += p_err ;



return output ;
 
}

void set_constant(float KP, float KI, float KD){
	kp = KP;
	ki = KI;
	kd = KD;
}


void in_kp(void){ kp += 0.01; }	  // Increase constant kp
void dr_kp(void){ kp -= 0.01; }	  // Decrease constant kp
void in_ki(void){ ki += 0.0001;}  // Increase constant ki
void dr_ki(void){ ki -= 0.0001;}  // Decrease constant ki
void in_kd(void){ kd += 0.05;}	  // Increase constant kd
void dr_kd(void){ kd -= 0.05;}	  // Decrease constant kd

int main(void)
{


    
    while (1) 
    {
    }
}

