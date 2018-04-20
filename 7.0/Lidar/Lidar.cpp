/*
 * Lidar.cpp
 *
 * Created: 10/24/2017 10:10:26 PM
 *  Author: iamra
 */ 

#include "Lidar.h"
#include "uart.h"

#define LIDAR_RECEIVE_TIME_LIMIT 720000
#define TIME_PER_CM 10

#define LIDAR_TRIGGER D,2
#define LIDAR_RECEIVE D,3

#define LIDAR_TCCR	TCCR1B
#define LIDAR_CSn0	CS10
//#define LIDAR_CSn1	CS11
//#define LIDAR_CSn2	CS12
#define LIDAR_TIMSK	TIMSK1
#define LIDAR_TOIE	TOIE1
#define LIDAR_TCNT	TCNT1
#define LIDAR_TIMER_OVERFLOW TIMER1_OVF_vect

Lidar::Lidar(void)
{
	Distance_in_cm = 0;
	Counter_overflow = 0;
	Time = 0;
	Receive_Flag = 1;
}

void Lidar::Lidar_Initialize_Timer(void)
{
	//REGISTER_SET1(LIDAR_TCCR,LIDAR_CSn0);	//Sets Prescalar to 1
	REGISTER_SET1(LIDAR_TIMSK,LIDAR_TOIE);	//Enables Timer Overflow Interrupt
	//REGISTER_CLEAR(LIDAR_TCNT);
}

void Lidar::Lidar_Start_Timer(void)
{
	REGISTER_SET1(LIDAR_TCCR,LIDAR_CSn0);
	REGISTER_CLEAR(LIDAR_TCNT);
}

void Lidar::Lidar_Stop_Timer(void)
{
	REGISTER_CLEAR(LIDAR_TCCR);
}

void Lidar::Lidar_Initialize(void)
{
	OUTPUT(LIDAR_TRIGGER);	//Sets Trigger pin as output
	SET(LIDAR_TRIGGER);		//Trigger pin internally pulled up
	
	INPUT(LIDAR_RECEIVE);	//Sets Receive pin as input
	
	Lidar_Initialize_Timer();
}

void Lidar::Lidar_Trigger(void)
{
	CLEAR(LIDAR_TRIGGER);	//Sets Trigger pin to logic 0 for transmitting laser
}

uint16_t Lidar::Lidar_Read(void)
{
	Lidar_Trigger();
	Counter_overflow = 0;
	while(!(READ(LIDAR_RECEIVE)));	//while rec bit is low
	
	Lidar_Start_Timer();
	
	while(READ(LIDAR_RECEIVE))	  //until rec bit is high
	{
		if (((Counter_overflow*TIMER_16BIT_LIMIT + LIDAR_TCNT)*(1.00/(F_CPU))*1000000 ) > LIDAR_RECEIVE_TIME_LIMIT)
		{
			UART0TransmitString("Hello");
			Receive_Flag = 0;	// Returns 0 if the distance of above 45m
			break;
		}
	}

	Lidar_Stop_Timer(); //stop 16 bit timer with no prescaler
		
	Time = ((Counter_overflow*TIMER_16BIT_LIMIT + LIDAR_TCNT)*(1.00/(F_CPU))*1000000 );
	if (Receive_Flag == 0 ){Time = 0;}
	Distance_in_cm = ((Time/TIME_PER_CM));

	SET(LIDAR_TRIGGER);
	return (Distance_in_cm);
	
}

void Lidar::Lidar_Increase_Counter(void)
{
	Counter_overflow++;
}

Lidar::~Lidar()
{
	
}
