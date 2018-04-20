/*
 * encoder-test.cpp
 *
 * Created: 10/15/2017 5:55:45 PM
 * Author : Subash Timilsina
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Encoder.h"
#include "uart.h"
#include "Motor.h"
#include "PID.h"

#define MOTOR_RPM	700.0	

extern signed char rcvdata[8];
Encoder e1(2);//,e2(2),e3(3),e4(4);

//int GetMotorOCR(int rpm)
//{
	//return((249.0/MOTOR_RPM)*rpm);
//}

int main(void)
{
   initUART2();
   initUART0();
   //UART0TransmitString("Hello..\n\r");
	Motor m1;
	PID pid;
	int temp;
	int dat = 0;
	pid.Set_Pid(0.81,0,3.68);
	m1.Initialise(2);
	int spoint ;
	m1.StopMotor();
	e1.Initialise();
	//e2.Initialise();
	//e3.Initialise();
	//e4.Initialise();
    while (1) 
    {	
		if (rcvdata[0]==16)
		dat +=50;
		if (rcvdata[1]==1)
		dat -=50;
		if (rcvdata[0]==32)
		{
			dat = 0;
			pid.Set_SP(0);
		//	m1.SetOcrValue(0);
			
		}
		if (rcvdata[1]==2)
		{
			UART0Transmit('\n');
			UART0TransmitData(pid.Get_P()*100);
			UART0Transmit(' ');
			UART0TransmitData(pid.Get_I()*1000);
			UART0Transmit(' ');
			UART0TransmitData(pid.Get_D()*100);
			UART0Transmit(' ');
			UART0TransmitData(dat);
			UART0Transmit('\n');
		}
		if (rcvdata[1]==4)
		pid.Set_Pid(0,0,0);

		if (dat>700)	dat = 700;
		if (dat<0) dat = 0;
		
		spoint = dat*PPR/3000.0;
		pid.Set_SP(spoint);
		
	
			temp = pid.Compute(e1.Get_Speed());
			m1.SetOcrValue(temp);
			if (rcvdata[0] == 1)
			{
				pid.Dcr_P();
 					if (pid.Get_P()<0.01)
 					pid.Set_P(0);
			}
			else if (rcvdata[0] == 2)
			pid.Inc_P();
			else if (rcvdata[0] == 4)
			{
				pid.Dcr_D();
 					if (pid.Get_D()<0.01)
 					pid.Set_D(0);
			}
			else if (rcvdata[0] == 8)
			pid.Inc_D();
			
			
			
			
			UART0TransmitData(spoint);
			UART0Transmit(' ');
			UART0TransmitData(e1.Get_Speed());
			UART0TransmitString("\r\n");
			
	
		
    }
}


ISR(INT_VECT2)
{
	if(bit_is_set(ENCODER2_CHAPORTPIN,ENCODER2_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
		e1.incCount();
	}
	else
	e1.dcrCount();
	
}


//ISR(INT_VECT1)
//{
	//if(bit_is_set(ENCODER1_CHAPORTPIN,ENCODER1_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e1.incCount();
	//}
	//else
	//e1.dcrCount();
	//
//}
//
//ISR(INT_VECT2)
//{
	//if(bit_is_set(ENCODER2_CHAPORTPIN,ENCODER2_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e2.incCount();		
	//}
	//else 
		//e2.dcrCount();
	//
//}
//ISR(INT_VECT3)
//{
	//if(bit_is_set(ENCODER3_CHAPORTPIN,ENCODER3_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e3.incCount();
	//}
	//else
	//e3.dcrCount();
//}
//
//ISR(INT_VECT4)
//{
	//if(bit_is_set(ENCODER4_CHAPORTPIN,ENCODER4_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
		//e4.incCount();
	//}
	//else
	//e4.dcrCount();
//}


ISR(TIMER1_COMPA_vect)
{
	e1.Calc_Speed();	
}