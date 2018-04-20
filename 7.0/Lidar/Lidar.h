/*
 * Lidar.h
 *
 * Created: 10/24/2017 10:09:57 PM
 *  Author: iamra
 */ 

#ifndef LIDAR_H_
#define LIDAR_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef TIMER_16BIT_LIMIT
#define TIMER_16BIT_LIMIT 65535
#endif

#include "Headers.h"
#define LIDAR_TIMER_OVERFLOW TIMER1_OVF_vect

class Lidar
{
	public:
	volatile uint16_t Distance_in_cm;
	volatile uint8_t Counter_overflow;
	volatile uint16_t Time;
	volatile bool Receive_Flag;
	
	public:
	Lidar(void);
	void Lidar_Initialize_Timer(void);
	void Lidar_Start_Timer(void);
	void Lidar_Stop_Timer(void);
	void Lidar_Initialize(void);
	void Lidar_Trigger(void);
	uint16_t Lidar_Read(void);
	void Lidar_Increase_Counter(void);
	
	~Lidar();
	};
	

#endif /* LIDAR_H_ */

/*Include this in main.cpp
ISR (LIDAR_TIMER_OVERFLOW)
{
	Lidar_Increase_Counter();
	CLEAR_REGISTER(LIDAR_TCNT);
}
*/