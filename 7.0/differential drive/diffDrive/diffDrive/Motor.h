#ifndef MOTOR_H
#define MOTOR_H



#include "headers.h"

     #define ICR_TOP   249
     #define MAX_VALUE 249
     #define MIN_VALUE 0




	//For motor 1


    #define PIN_F1 D,7
    #define PIN_B1 D,6

    #define PIN_PWM1		D,4
    #define PWM_TCCRA1		TCCR1A
    #define PWM_TCCRB1		TCCR1B
    #define PWM_ICR1		ICR1
    #define PWM_OCR1		OCR1A

    #define PWM_1COM0		COM1A0
    #define PWM_1COM1		COM1A1

    #define PWM_1WGM0		WGM10
    #define PWM_1WGM1		WGM11
    #define PWM_1WGM2		WGM12
    #define PWM_1WGM3		WGM13
    #define PWM_1CS0		CS10
    #define PWM_1CS1		CS11
    #define PWM_1CS2		CS12

    //For motor 2

    #define PIN_F2 A,6
    #define PIN_B2 A,7

    #define PIN_PWM2		D,5
    #define PWM_TCCRA2		TCCR1A
    #define PWM_TCCRB2		TCCR1B
    #define PWM_ICR2		ICR1
    #define PWM_OCR2		OCR1B

    #define PWM_2COM0		COM1B0
    #define PWM_2COM1		COM1B1

    #define PWM_2WGM0		WGM10
    #define PWM_2WGM1		WGM11
    #define PWM_2WGM2		WGM12
    #define PWM_2WGM3		WGM13
    #define PWM_2CS0		CS10
    #define PWM_2CS1		CS11
    #define PWM_2CS2		CS12


class Motor
{

     private:
		uint8_t num;
     public:
        void Initialise(uint8_t no);

        void InitPWM();

        void setForwardDirection();
        void setReverseDirection();
        void StopMotor();
        void SetOcrValue(int x);
};

#endif // MOTOR_H
