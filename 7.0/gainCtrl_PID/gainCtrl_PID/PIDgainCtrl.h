/*
 * PIDgainCtrl.h
 *
 * Created: 1/5/2018 7:28:07 PM
 *  Author: Sherlock
 */


#ifndef PIDGAINCTRL_H_
#define PIDGAINCTRL_H_

/*----------------------- TO be defined by user ----------------------------------*/

//Select pins
#define P_gainInc      PINF0
#define P_gainDec      PINF5
#define I_gainInc      PINF1
#define I_gainDec      PINF4
#define D_gainInc      PINF2
#define D_gainDec      PINF3

//Data direction registers
#define P_gainInc_ddr     DDRF
#define P_gainDec_ddr     DDRF
#define I_gainInc_ddr     DDRF
#define I_gainDec_ddr     DDRF
#define D_gainInc_ddr     DDRF
#define D_gainDec_ddr     DDRF


//Choose Port
#define P_gainInc_port     PORTF
#define P_gainDec_port     PORTF
#define I_gainInc_port     PORTF
#define I_gainDec_port     PORTF
#define D_gainInc_port     PORTF
#define D_gainDec_port     PORTF

//Read pin
#define P_gainInc_pin     PINF
#define P_gainDec_pin     PINF
#define I_gainInc_pin     PINF
#define I_gainDec_pin     PINF
#define D_gainInc_pin     PINF
#define D_gainDec_pin     PINF

/*------------------------------------------------------------------------*/


//Button pressed
#define button1_p bit_is_clear(P_gainInc_pin,P_gainInc)     //Button 1 pressed
#define button2_p bit_is_clear(P_gainDec_pin,P_gainDec)     //Button 2 pressed
#define button3_p bit_is_clear(I_gainInc_pin,I_gainInc)     //Button 3 pressed
#define button4_p bit_is_clear(I_gainDec_pin,I_gainDec)     //Button 4 pressed
#define button5_p bit_is_clear(D_gainInc_pin,D_gainInc)     //Button 4 pressed
#define button6_p bit_is_clear(D_gainDec_pin,D_gainDec)	     //Button 5 pressed

//Button pressed
#define button1_np (!bit_is_clear(P_gainInc_pin,P_gainInc))     //Button 1 not pressed
#define button2_np (!bit_is_clear(P_gainDec_pin,P_gainDec))     //Button 2 not pressed
#define button3_np (!bit_is_clear(I_gainInc_pin,I_gainInc))     //Button 3 not pressed
#define button4_np (!bit_is_clear(I_gainDec_pin,I_gainDec))     //Button 4 not pressed
#define button5_np (!bit_is_clear(D_gainInc_pin,D_gainInc))     //Button 4 not pressed
#define button6_np (!bit_is_clear(D_gainDec_pin,D_gainDec))     //Button 5 not pressed



void updatePIDgain() ;
void init_PIDgainCtrl();

#endif /* PIDGAINCTRL_H_ */