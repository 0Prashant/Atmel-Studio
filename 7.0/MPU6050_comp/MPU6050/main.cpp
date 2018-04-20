/*
 * MPU6050.cpp
 *
 * Created: 2/13/2018 3:55:03 PM
 * Author : Sherlock
 */ 
 #define F_CPU 16000000UL
#include "MPU6050.h"
#include <avr/io.h>
#include "UART.h"
#include "Complementary_Filter.h"
 


int main()
{
 uartInitialize();
  mpuInitialize();
 	
  while (1)
  {
     getAccelAngle();

     uartTransmitInteger(accelAngle.YAxis);
     uartTransmitChar('\n');
    
       	  
  }

  
}
