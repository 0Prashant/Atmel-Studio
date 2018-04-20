/*
 * diffDrive.cpp
 *
 * Created: 2/1/2018 2:28:46 PM
 * Author : Sherlock
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include "headers.h"
#include "Motor.h"
#include "uart.h"
#define Pneumetic1 A,1
#define Pneumetic2 A,2

int robotVelocity;

int VelX;
int Yaw;
int V1,V2;
Motor M1,M2;

void initAll(){
	 M1.Initialise(1);
	 M2.Initialise(2);

	 robotVelocity = 100;
	 VelX = 0;
	 Yaw = 0;
	OUTPUT(Pneumetic1) ;
	OUTPUT(Pneumetic2) ;
	 uart0_init(UART_BAUD_SELECT(9600,F_CPU));
	 sei();

}

void recieveControlCharacter(){
	char data = uart0_getc();

	switch(data){
		case 'B':{
			VelX = robotVelocity;
			Yaw = 0;
			break;
		}

		case 'F':{
			VelX = -robotVelocity;
			Yaw = 0;
			break;
		}
		case 'G':{
			Yaw = -robotVelocity;
			VelX = robotVelocity;
			break;
		}
		case 'I':{
			 Yaw = robotVelocity;
			 VelX = robotVelocity;
			 break;
		}
		case 'S':{
			Yaw = 0;
			VelX = 0;
			break;
		}
		case 'L':{
			Yaw =-robotVelocity;
			VelX =0;
			break;
			//SET(Pneumetic)	;
			//break;
		}


		case 'R':{
			Yaw = robotVelocity;
			VelX= 0;
			break;
			//CLEAR(Pneumetic);
			//break;
		}
		case 'V':
		{	SET(Pneumetic1);
			break;
		}
		case 'v':
		{
			CLEAR(Pneumetic1);
			break;
		}
		case 'X':
		{	SET(Pneumetic2);
			break;
		}
		case 'x':
		{
			CLEAR(Pneumetic2);
			break;
		}

		case '0':{
			robotVelocity = 0;
			break;
		}
		case '1':{
			robotVelocity = 50;
			break;
		}



		case '2':{
			robotVelocity = 100;
			break;
		}

		case '3':{
			robotVelocity = 150;
			break;
		}

		case '4':{
			robotVelocity = 200;
			break;
		}
		case '5':{
			robotVelocity = 250;
			break;
		}
		case '6':{
			robotVelocity = 300;
			break;
		}
		case '7':{
			robotVelocity = 350;
			break;
		}
		case '8':{
			robotVelocity = 400;
			break;
		}
		case '9':{
			robotVelocity = 400;
			break;
		}
		case 'q':{
			robotVelocity = 400;
			break;
		}







	}







}

void updateVelocity(){

	    V1 = 0.5*(VelX+Yaw);
	    V2 = 0.5*(VelX-Yaw);
		if(V1 > 200)	V1 = 200;
		if(V2 > 200)	V2 = 200;
	    M1.SetOcrValue(V1);
	    M2.SetOcrValue(V2);

}


int main(void)
{
      initAll();
	//DDRA = 0XFF;



    while (1)
    {

	 recieveControlCharacter();
	 updateVelocity();

    }
}

