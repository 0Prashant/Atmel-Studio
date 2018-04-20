/*
 * Joydata.h
 *
 * Created: 10/12/2017 7:11:34 PM
 *  Author: Subash Timilsina
 */ 

#include "Wheel.h"


Encoder e[4];
volatile bool pidflag = false;
float coupling_matrix[4][3] = {{-0.707,0.707,-0.707},{0.707,0.707,0.707},{-0.707,0.707,0.707},{0.707,0.707,-0.707}};


void Wheel::init()
{
	
	robot_rpm = 50;
	for(i=0;i<4;i++)
	{
		velocity_motor[i] = 0;
		velocity_robot[i] = 0;
		m[i].Initialise(i+1);
		e[i].Initialise(i+1);
		p[i].Set_Pid(0,0,0);
		//p[i].Set_Pid(0,0,0);
	}
	
	reset_robotvelocity();	
}

void Wheel::get_joystick_data(char data)
{
		/************* change the values of pid and set-point ****************/
			switch(data)
			{
			case 'i':
			{
				robot_rpm +=20;
				break;
			}
			case 'd':
			{
				robot_rpm -=20;
				break;
			}
			case 'm':
			{
				p[0].Dcr_P();
				break;
			}
			case 'n':
			{
				p[0].Inc_P();
				break;
			}
			case 'u':
			{
				p[0].Dcr_I();
				break;
			}
			case 'v':
			{
				p[0].Inc_I();
				break;
			}
			case 'x':
			{
				p[0].Dcr_D();
				break;
			}
			case 'y':
			{
				p[0].Inc_D();
				break;
			}
			/***************** Set-point changing characters *****************/
				case 'f':
				{
					velocity_robot[0] = 0;
					velocity_robot[1] = robot_rpm;
					velocity_robot[2] = 0;
					break;

				}
				case 'b':
				{
					velocity_robot[0] = 0;
					velocity_robot[1] = -robot_rpm;
					velocity_robot[2] = 0;
					break;

				}
				case 'r':
				{
					velocity_robot[0] = 0;
					velocity_robot[1] = -robot_rpm;
					velocity_robot[2] = 0;
					break;

				}
				case 'l':
				{
					velocity_robot[0] = 0;
					velocity_robot[1] = robot_rpm;
					velocity_robot[2] = 0;
					break;

				}
				case 'c':
				{
					velocity_robot[0] = 0;
					velocity_robot[1] = 0;
					velocity_robot[2] = -robot_rpm;
					break;

				}
				case 'a':
				{
					velocity_robot[0] = 0;
					velocity_robot[1] = 0;
					velocity_robot[2] = robot_rpm;
					break;

				}
				case 's':
				{
					reset_robotvelocity();
					break;
				}
				case 'p':
				{
					UART3TransmitString("\n\r");
					UART3TransmitData(p[0].Get_P()*1000);
					UART3Transmit(' ');
					UART3TransmitData(p[0].Get_I()*1000);
					UART3Transmit(' ');
					UART3TransmitData(p[0].Get_D()*100);
					UART3TransmitString("\n\r");
					break;
				}
				default: break;
			}
			for(i = 1; i<4 ;i++)
			{
				p[i].Set_Pid(p[0].Get_P(),p[0].Get_I(),p[0].Get_D());
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
		ocr_motor[i] = velocity_motor[i]*PPR/3000.0;
		velocity_robot[i] = 0;
		p[i].Set_SP(ocr_motor[i]);
    }
	  
}

void Wheel::update_wheel_velocity()
{
	if(pidflag)
	{
		for(i = 0; i<4 ; i++)
		{
			m[i].SetOcrValue(p[i].Compute(e[i].Get_Speed()));
		}
		
		pidflag = false;
	}
		  UART2TransmitData(20);
		  UART2Transmit(' ');
		  UART2TransmitData(-20);
		  UART2Transmit(' ');
		  UART2TransmitData(ocr_motor[0]);
		  UART2Transmit(' ');
		  UART2TransmitData(e[0].Get_Speed());
		  UART2TransmitString("\r\n");

}
	

void Wheel::reset_robotvelocity()
{
	for(i = 0; i<4 ; i++)
	{
		velocity_robot[i] = 0;
	}
}


ISR(INT_VECT1)
{
	if(bit_is_set(ENCODER1_CHAPORTPIN,ENCODER1_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
	e[0].incCount();
	}
	else
	e[0].dcrCount();

}

ISR(INT_VECT2)
{
	if(bit_is_set(ENCODER2_CHAPORTPIN,ENCODER2_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
	e[1].incCount();
	}
	else
	e[1].dcrCount();


}
ISR(INT_VECT3)
{
	if(bit_is_set(ENCODER3_CHAPORTPIN,ENCODER3_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
	e[2].incCount();
	}
	else
	e[2].dcrCount();

}

ISR(INT_VECT4)
{
	if(bit_is_set(ENCODER4_CHAPORTPIN,ENCODER4_CHBPIN))		//ENCODER_CHAPORTPIN,ENCODER_CHBPIN
	{
	e[3].incCount();
	}
	else
	e[3].dcrCount();

}


ISR(TIMER1_COMPA_vect)
{
	e[0].Calc_Speed();
	e[1].Calc_Speed();
	e[2].Calc_Speed();
	e[3].Calc_Speed();
	pidflag = true;
}