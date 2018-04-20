/*
 * Joydata.h
 *
 * Created: 10/12/2017 7:11:34 PM
 *  Author: Subash Timilsina
 */ 

#include "Wheel.h"

float coupling_matrix[4][3] = {{-0.707,0.707,-0.707},{0.707,0.707,0.707},{-0.707,0.707,0.707},{0.707,0.707,-0.707}};

void Wheel::init()
{
	
	robot_rpm = 50;
	for(int i=0;i<4;i++)
	{
		velocity_motor[i] = 0;
		velocity_robot[i] = 0;
		m[i].Initialise(i+1);
		//e[i].Initialise(i+1);
		//p[i].Set_Pid(0,0,0);
	}

	
}

 void Wheel::get_joystick_data(char data)
 {
	
	switch(data)
	{
		case 'F':
		{
			velocity_robot[0] = 0;
			velocity_robot[1] = robot_rpm;
			velocity_robot[2] = 0;
			break;
		}
		case 'B':
		{
			velocity_robot[0] = 0;
			velocity_robot[1] = -robot_rpm;
			velocity_robot[2] = 0;
			break;
		}
		case 'R':
		{
			velocity_robot[0] = -robot_rpm;
			velocity_robot[1] = 0;
			velocity_robot[2] = 0;
			break;
		}
		case 'L':
		{
			velocity_robot[0] = robot_rpm;
			velocity_robot[1] = 0;
			velocity_robot[2] = 0;
			break;
		}
		case 'G':
		{
			velocity_robot[0] = 0;
			velocity_robot[1] = 0;
			velocity_robot[2] = robot_rpm;
			break;
		}
		case 'I':
		{
			velocity_robot[0] = 0;
			velocity_robot[1] = 0;
			velocity_robot[2] = -robot_rpm;
			break;
		}
		case '0':
		{
			robot_rpm = 80;
			break;
		}
		case '1':
		{
			robot_rpm = 100;
			break;
		}
		case '2':
		{
			robot_rpm = 120;
			break;
		}
		case '3':
		{
			robot_rpm = 140;
			break;
		}
		case '4':
		{
			robot_rpm = 180;
			break;
		}
		case 'S':
		{
			reset_robvel();
			break;
		}
	}
	if (robot_rpm>MAX_RPM) robot_rpm = MAX_RPM;
	else if (robot_rpm<0)	robot_rpm = 0;

 }

void Wheel::calculate_wheel_velocity()
{
    for(i=0;i<4;i++)
    {
        velocity_motor[i] = 0;
        for(j=0;j<3;j++)
        {
             velocity_motor[i] += velocity_robot[j] * coupling_matrix[i][j];
        }
		
    }
	
    for(i=0;i<4;i++)
    {
		ocr_motor[i] = (int(249*velocity_motor[i])/(MAX_RPM));
		//ocr_motor[i] = velocity_motor[i]*PPR/3000.0;
		//velocity_robot[i] = 0;
		//p[i].Set_SP(ocr_motor[i]);
    }
	  
}

void Wheel::update_wheel_velocity()
{
	//if(pidflag)
	//{
		//for(int i = 0; i<4 ; i++)
		//{
			//m[i].SetOcrValue(p[i].Compute(e[i].Get_Speed()));
		//}
		//pidflag = false;
	//}	  
	for(i = 0; i<4 ; i++)
	{
		m[i].SetOcrValue(ocr_motor[i]);
	}
}
	

void Wheel::reset_robvel()
{
	for(i=0;i<4;i++)
	{
		velocity_robot[i] = 0;
	}
}


//ISR(INT_VECT1)
//{
	//if(bit_is_set(ENCODER1_CHAPORTPIN,ENCODER1_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
	//e[0].incCount();
	//}
	//else
	//e[0].dcrCount();
//
//}
//
//ISR(INT_VECT2)
//{
	//if(bit_is_set(ENCODER2_CHAPORTPIN,ENCODER2_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
	//e[1].incCount();
	//}
	//else
	//e[1].dcrCount();
//
//
//}
//ISR(INT_VECT3)
//{
	//if(bit_is_set(ENCODER3_CHAPORTPIN,ENCODER3_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
	//e[2].incCount();
	//}
	//else
	//e[2].dcrCount();
//
//}
//
//ISR(INT_VECT4)
//{
	//if(bit_is_set(ENCODER4_CHAPORTPIN,ENCODER4_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	//{
	//e[3].incCount();
	//}
	//else
	//e[3].dcrCount();
//
//}
//
//
//ISR(TIMER1_COMPA_vect)
//{
	//e[0].Calc_Speed();
	//e[1].Calc_Speed();
	//e[2].Calc_Speed();
	//e[3].Calc_Speed();
	//count++;
	//pidflag = true;
//}