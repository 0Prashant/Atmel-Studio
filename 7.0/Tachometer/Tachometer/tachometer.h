/*
 * tachometer.h
 *
 * Created: 10/7/2017 9:51:07 AM
 * Author : Rishav
 */ 
#ifndef TACHOMETER_H_
#define TACHOMETER_H_

 #ifndef F_CPU
 #define F_CPU 16000000UL
 #endif /*F_CPU*/

 #define PPR           1   // Pulse per rotation
 #define SAMPLE_TIME   0.5 // Sample time in seconds

 void init_tachometer(void);

#endif /*TACHOMETER_H_*/

