#include "Motor.h"



void Motor::Initialise(uint8_t no)
{
	num = no;
	InitPWM();

	StopMotor();
	SetOcrValue(0);

}

void Motor::InitPWM()
{
	if (num==1)
	{
		OUTPUT(PIN_F1);
		OUTPUT(PIN_B1);

		OUTPUT(PIN_PWM1);

		PWM_TCCRA1	|=  ( 1 << PWM_1COM1 ) | ( 1 << PWM_1WGM1 );														//
		PWM_TCCRB1	|= (1<<PWM_1WGM2) | ( 1 << PWM_1WGM3 ) | ( 1 << PWM_1CS1);									//PRESCALAR 8
		PWM_ICR1		 =         ICR_TOP;
	}
	else if(num == 2)
	{
		OUTPUT(PIN_F2);
		OUTPUT(PIN_B2);

		OUTPUT(PIN_PWM2);

		PWM_TCCRA2	|=  ( 1 << PWM_2COM1 ) | ( 1 << PWM_2WGM1 );														//
		PWM_TCCRB2	|=  (1<<PWM_2WGM2) | ( 1 << PWM_2WGM3 ) | ( 1 << PWM_2CS1);									//PRESCALAR 8
		PWM_ICR2		 =         ICR_TOP;
	}

}

void Motor::setForwardDirection()
{
	switch(num)
	{
		case 1:
			SET	(PIN_F1);
			CLEAR	(PIN_B1);
			break;
		case 2:
			SET	(PIN_F2);
			CLEAR	(PIN_B2);
			break;
	}


}
void Motor::setReverseDirection()
{
	switch(num)
	{
		case 1:
			CLEAR	(PIN_F1);
			SET	(PIN_B1);
			break;
		case 2:
			CLEAR	(PIN_F2);
			SET	(PIN_B2);
			break;
	}

}

void Motor::StopMotor()
{
	switch(num)
	{
		case 1:
			PWM_OCR1 = 0;
			SET	(PIN_F1);
			SET	(PIN_B1);
			break;

		case 2:
			PWM_OCR2 = 0;
			SET	(PIN_F2);
			SET	(PIN_B2);
			break;
	}
}


void Motor::SetOcrValue(int Ocr)
{
    if (Ocr > 0)
        setForwardDirection();

	if( Ocr >= MAX_VALUE){
		Ocr = MAX_VALUE;
	}

	if( Ocr < 0){
		Ocr = -Ocr;
		setReverseDirection();
	}

	switch(num)
	{
		case 1:
			PWM_OCR1	= Ocr;
			break;
		case 2:
			PWM_OCR2	= Ocr;
			break;

	}
}
