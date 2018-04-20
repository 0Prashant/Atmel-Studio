#ifndef MOTOR_H
#define MOTOR_H



	#include "headers.h"

     #define ICR_TOP   249
     #define MAX_VALUE 249
     #define MIN_VALUE 0




	//For motor 1


    #define DD_F1 H,4
    #define DD_B1 H,3

    #define DD_PWM1			E,3
    #define PWM_TCCRA1		TCCR3A
    #define PWM_TCCRB1		TCCR3B
    #define PWM_ICR1			ICR3
    #define PWM_OCR1			OCR3A

    #define PWM_1COM0		COM3A0
    #define PWM_1COM1		COM3A1

    #define PWM_1WGM0		WGM30
    #define PWM_1WGM1		WGM31
    #define PWM_1WGM2		WGM32
    #define PWM_1WGM3		WGM33
    #define PWM_1CS0			CS30
    #define PWM_1CS1			CS31
    #define PWM_1CS2			CS32

    //For motor 2

    #define DD_F2 H,6
    #define DD_B2 B,4

    #define DD_PWM2			B,5
    #define PWM_TCCRA2		TCCR1A
    #define PWM_TCCRB2		TCCR1B
    #define PWM_ICR2			ICR1
    #define PWM_OCR2			OCR1A

    #define PWM_2COM0		COM1A0
    #define PWM_2COM1		COM1A1

    #define PWM_2WGM0		WGM10
    #define PWM_2WGM1		WGM11
    #define PWM_2WGM2		WGM12
    #define PWM_2WGM3		WGM13
    #define PWM_2CS0			CS10
    #define PWM_2CS1			CS11
    #define PWM_2CS2			CS12

//For motor 3

    #define DD_F3 G,5
    #define DD_B3 H,5

    #define DD_PWM3			B,6
    #define PWM_TCCRA3		TCCR1A
    #define PWM_TCCRB3		TCCR1B
    #define PWM_ICR3			ICR1
    #define PWM_OCR3			OCR1B

    #define PWM_3COM0		COM1B0
    #define PWM_3COM1		COM1B1

    #define PWM_3WGM0		WGM10
    #define PWM_3WGM1		WGM11
    #define PWM_3WGM2		WGM12
    #define PWM_3WGM3		WGM13
    #define PWM_3CS0			CS10
    #define PWM_3CS1			CS11
    #define PWM_3CS2			CS12


//For motor 4

    #define DD_F4 E,4
    #define DD_B4 E,5

    #define DD_PWM4			B,7
    #define PWM_TCCRA4		TCCR1A
    #define PWM_TCCRB4		TCCR1B
    #define PWM_ICR4			ICR1
    #define PWM_OCR4			OCR1C

    #define PWM_4COM0		COM1C0
    #define PWM_4COM1		COM1C1

    #define PWM_4WGM0		WGM10
    #define PWM_4WGM1		WGM11
    #define PWM_4WGM2		WGM12
    #define PWM_4WGM3		WGM13
    #define PWM_4CS0			CS10
    #define PWM_4CS1			CS11
    #define PWM_4CS2			CS12



class Motor
{

     private:
		uint8_t num:1;	
     public:
        void Initialise(uint8_t no);

        void InitPWM();

        void SetForwardDirection();
        void SetReverseDirection();
        void StopMotor();
        void SetOcrValue(int x);
};

#endif // MOTOR_H
