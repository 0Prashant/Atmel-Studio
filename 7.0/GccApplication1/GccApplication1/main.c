/*
 * GccApplication1.c
 *
 * Created: 20/05/2017 10:01:17 AM
 * Author : Sushma
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

void on()
	{
		PORTD = 0b11111111;
		_delay_ms(1000);
	}
void off()
	{
		PORTD = 0b00000000;
		_delay_ms(1000);
	}	
void zero()
{
	PORTD = 0b00111111;
}
void one()
{
	PORTD = 0b00000110;
}
void two()
{
	PORTD = 0b01011011;
}
void three()
{
	PORTD = 0b01001111;
}
void four()
{
	PORTD = 0b01100110;
}
void five()
{
	PORTD = 0b01101101;
}
void six()
{
	PORTD = 0b01111101;
}
void seven()
{
	PORTD = 0b00100111;
}
void eight()
{
	PORTD = 0b01111111;
}	
void nine()
{
	PORTD = 0b01101111;
}
void szero()
{
	PORTA = 0b00111111;
	_delay_ms(300);
}
void sone()
{
	PORTA = 0b00000110;
	_delay_ms(300);
}
void stwo()
{
	PORTA = 0b01011011;
	_delay_ms(300);
}
void sthree()
{
	PORTA = 0b01001111;
	_delay_ms(300);
}
void sfour()
{
	PORTA = 0b01100110;
	_delay_ms(300);
}
void sfive()
{
	PORTA = 0b01101101;
	_delay_ms(300);
}
void ssix()
{
	PORTA = 0b01111101;
	_delay_ms(300);
}
void sseven()
{
	PORTA = 0b00100111;
	_delay_ms(300);
}
void seight()
{
	PORTA = 0b01111111;
	_delay_ms(300);
}
void snine()
{
	PORTA = 0b01101111;
	_delay_ms(300);
}
int main()
{
	DDRD= 0xFF	;
	PORTD = 0b00000000;
    /* Replace with your application code */
    for(int i=0;i<10;i++) 
    {
		
		for(int j=0;j<10;j++)
		{
			switch (i)
			{
				case 0:
				zero();
				break;
				case 1:
				one();
				break;
				case 2:
				two();
				break;
				case 3:
				three();
				break;
				case 4:
				four();
				break;
				case 5:
				five();
				break;
				case 6:
				six();
				break;
				case 7:
				seven();
				break;
				case 8:
				eight();
				break;
				case 9:
				nine();
				break;
			}
			switch (j)
			{
				case 0:
					szero();
					break;
				case 1:
					sone();
					break;
				case 2:
					stwo();
					break;
				case 3:
					sthree();
					break;
				case 4:
					sfour();
					break;
				case 5:
					sfive();
					break;
				case 6:
					ssix();
					break;
				case 7:
					sseven();
					break;
				case 8:
					seight();
					break;
				case 9:
					snine();
					break;
			}
			
		}
    }
	return 0;
}

