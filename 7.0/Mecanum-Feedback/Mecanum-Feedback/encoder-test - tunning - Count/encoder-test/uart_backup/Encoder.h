/* 
* Encoder.h
*
* Created: 10/15/2017 5:57:05 PM
* Author: Subash Timilsina
*/


#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <avr/io.h>
#include <avr/interrupt.h>
#include "headers.h"

#ifndef F_CPU	
#define F_CPU		16000000UL
#endif

#define	 CLOCKWISE			1
#define	 ANTICLOCKWISE		0
#define  ENCODER_CHANNELA	D,3
#define	 ENCODER_CHANNELB	A,3
#define	 ENCODER_INT		INT3

#define	 ENCODER_CHAPORTPIN	 PINA
#define	 ENCODER_CHBPIN		 PA3			
#define	 INT_ISC1			ISC31
#define	 INT_INTF			INTF3

#define  INT_VECT			INT3_vect

#define  DELAYTIMEMS		20.0

#define	 PPR	200.0

class Encoder
{
	private:
		volatile int pprcount;
		volatile int encmotor_rpm;
		bool motordirection;
	public:
	Encoder():pprcount(0),encmotor_rpm(0){};
	void Initialise();
	void Init_Interrupts();
	void Init_Timers();
	void incCount(){pprcount++;};
	void dcrCount(){pprcount--;};
	int Get_count(){return pprcount;};
	void Set_count(int val){pprcount = val;};
	void Set_motorRPM(int RPM){encmotor_rpm = RPM;};
	int  Get_motorRPM(){return encmotor_rpm;};
	void Set_motorDir(bool dir){motordirection = dir;};
	bool  Get_motorDir(){return motordirection;};
}; 

#endif //__ENCODER_H__
