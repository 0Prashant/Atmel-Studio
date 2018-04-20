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
#define Pneumetic A,0
int robotVelocity;
int VelX;
int Yaw;
int V1,V2;
Motor M1,M2;

void initAll()
{
	 M1.Initialise(1);
	 M2.Initialise(2);

	 robotVelocity = 100;
	 VelX = 0;
	 Yaw = 0;

	 uart0_init(UART_BAUD_SELECT(9600,F_CPU));
	 sei();

}

void recieveControlCharacter()
{
	char data = uart0_getc();
	switch(data)
	{
		case 'F':
		{
			VelX = robotVelocity;
			Yaw = 0;
			break;
		}

		case 'B':
		{
			VelX = -robotVelocity;
			Yaw = 0;
			break;
		}
		case 'G':
		{
			Yaw = -(robotVelocity/2);
			VelX = robotVelocity;
			break;
		}
		case 'I':
		{
			 Yaw = robotVelocity/2;
			 VelX = robotVelocity;
			 break;
		}
		case 'H':
		{
			Yaw = -(robotVelocity/2);
			VelX = -robotVelocity;
			break;
		}
		case 'J':
		{
			Yaw = robotVelocity/2;
			VelX = -robotVelocity;
			break;
		}
		case 'X':
		{
			SET(Pneumetic);
		}
		case 'x':
		{
			CLEAR(Pneumetic);
		}
		case 'S':
		{
			Yaw = 0;
			VelX = 0;
			break;
		}
		case 'R':
		{
			 Yaw =-robotVelocity;
			 VelX =0;
			 break;
		}
		case 'L':
		{
			 Yaw = robotVelocity;
			 VelX= 0;
			   break;
		}

		case '0':
		{
			robotVelocity = 0;
			break;
		}
		case '1':
		{
			robotVelocity = 25;
			break;
		}
		case '2':
		{
			robotVelocity = 50;
			break;
		}

		case '3':
		{
			robotVelocity = 75;
			break;
		}

		case '4':
		{
			robotVelocity = 100;
			break;
		}
		case '5':
		{
			robotVelocity = 125;
			break;
		}
		case '6':
		{
			robotVelocity = 150;
			break;
		}
		case '7':
		{
			robotVelocity = 175;
			break;
		}
		case '8':
		{
			robotVelocity = 200;
			break;
		}
		case '9':
		{
			robotVelocity = 225;
			break;
		}
		case 'q':
		{
			robotVelocity = 245;
			break;
		}
	}
	 if (robotVelocity>249)
	 {
		 robotVelocity = 249;
	 }
	 if (robotVelocity<0)
	 {
		robotVelocity =0;
	 }
}

void updateVelocity()
{
	    V1 = 0.5*(VelX+Yaw);
	    V2 = 0.5*(VelX-Yaw);

	    M1.SetOcrValue(V1);
	    M2.SetOcrValue(V2);
}



int main(void)
{
    initAll();
    while (1)
    {
	 recieveControlCharacter();
	 updateVelocity();
    }
}

