/* 
* PID.h
*
* Created: 10/28/2017 11:53:41 AM
* Author: Subash Timilsina
*/


#ifndef __PID_H__
#define __PID_H__

#include <avr/io.h>
#include <math.h>

class PID
{
	private:
		float kp,ki,kd;
		int sp; 
		int error , lastinput , errorsum;
	
	public:
		int dterm;
		PID():kp(0),ki(0),kd(0),sp(0),error(0),lastinput(0),errorsum(0){};
		void Set_P(float kP){kp = kP;};
		void Set_I(float kI){ki = kI;};
		void Set_D(float kD){kd = kD;};	
		void Set_SP(int sP){sp=sP;};
		int  Get_SP(){return sp;};
		void Inc_P(){kp+=0.1;};
		void Inc_I(){ki+=0.1;};
		void Inc_D(){kd+=0.1;};
		void Dcr_P(){kp-=0.1;};
		void Dcr_I(){ki-=0.1;};
		void Dcr_D(){kd-=0.1;};
		void Set_Pid(float kP,float kI,float kD);
		float Get_P();
		float Get_I();
		float Get_D();
		int Compute(int input);

}; 

#endif //__PID_H__
