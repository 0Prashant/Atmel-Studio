/* 
* PID.cpp
*
* Created: 10/28/2017 11:53:40 AM
* Author: Subash Timilsina
*/


#include "PID.h"

void PID::Set_Pid(float kP,float kI,float kD)
{
	kp = kP;
	ki = kI;
	kd = kD;	
}

float PID::Get_P()
{
	return kp;
}

float PID::Get_I()
{
	return ki;
}

float PID::Get_D()
{
	return kd;
}

int PID::Compute(int input)
{
	error = sp - input;
	
	//pterm calculation
	
	int pterm = error*kp;
	
	//iterm calculation
	 
	 errorsum += error;
	 int iterm = errorsum*ki;
	 
	 //dterm calculation
	 
	 dterm = kd*(input-lastinput);
	
	lastinput = input;
	
	int cv = 0;
	if (fabs(error)>3)//error tolerance
	{
		cv = pterm + iterm - dterm;
	}
	
	return cv;
}


