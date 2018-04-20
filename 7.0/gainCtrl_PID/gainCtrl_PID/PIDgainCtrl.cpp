/*
 * PIDgainCtrl.cpp
 *
 * Created: 1/5/2018 7:28:53 PM
 *  Author: Sherlock
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include "PIDgainCtrl.h"
#include "uart.h"

//Flags
bool flagOne=true, flagTwo=true , flagThree=true, flagFour=true, flagFive=true, flagSix=true;

void init_PIDgainCtrl(){
	
	//Data direction as input
	P_gainInc_ddr |= (0<<P_gainInc);
        P_gainDec_ddr |= (0<<P_gainDec);
	I_gainInc_ddr |= (0<<I_gainInc);
	I_gainDec_ddr |= (0<<I_gainDec);
	D_gainInc_ddr |= (0<<D_gainInc);
	D_gainDec_ddr |= (0<<D_gainDec);
 
        //Pull-ups
	P_gainInc_port |= (1<<P_gainInc);
	P_gainDec_port |= (1<<P_gainDec);
        I_gainInc_port |= (1<<I_gainInc);
	I_gainDec_port |= (1<<I_gainDec);
	D_gainInc_port |= (1<<D_gainInc);
	D_gainDec_port |= (1<<D_gainDec);	
	
}

void updatePIDgain(){
	
	//Check pin state and do task
	 if (button1_p && flagOne){
		 uart0_puts("P Gain Increase \n");
		 flagOne = false;
		

	 }
	 if (button2_p && flagTwo){

		 uart0_puts("P Gain Decrease \n");
		 flagTwo = false;
		 

	 }
	 if (button3_p && flagThree){

		 uart0_puts("I Gain Increase \n");
		 flagThree = false;
		 
	 }
	 if (button4_p && flagFour){

		 uart0_puts("I Gain Decrease \n");
		 flagFour = false;
		 

	 }
	 if (button5_p && flagFive){

		uart0_puts("D Gain Increase \n");
		flagFive = false;
		

	 }
	 if (button6_p && flagSix){

		 uart0_puts("D Gain Decrease \n");
		 flagSix = false;
		
	 }


	  //Set Flag
         if (button1_np && button2_np && button3_np && button4_np && button5_np && button6_np){

	         flagOne   = true;
		 flagTwo   = true;
		 flagThree = true;
		 flagFour  = true;
		 flagFive  = true;
		 flagSix   = true;

         }



  }