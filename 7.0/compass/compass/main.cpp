/*
 * compass.cpp
 *
 * Created: 12/1/2017 5:57:31 PM
 * Author : Prashant
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "TWI.h"
#include "uart0.h"
#include <math.h>
int x,y,z;

void initialize_compass()
{
	i2c_initialize(100000,0);	//initialize i2c bus as 50 kHz frequency by using 0 prescalar (see TWSR register)
	i2c_start();			//start condition
	i2c_writedata(0x3C,1);	//initializing compass address as 0x3C for write
	i2c_writedata(0x00,1);			//set pointer to address 0x00
	i2c_writedata(0x70,1);			//write data in 0x00 of compass (Configuration Register A)
	i2c_writedata(0xA0,1);			//burst write to 0x01 of compass (Configuration Register B)
	i2c_writedata(0x00,0);			//burst write to 0x02 of compass (continuous Mode)
	i2c_stop();
	_delay_ms(10);
	
// 	i2c_start();
// 	i2c_writedata(0x3C);
// 	i2c_writedata(0x09);
// 	i2c_writedata
// 	i2c_stop();
}

void getdata_compass()
{
	i2c_start();
	i2c_writedata(0x3D,1);
	i2c_writedata(0x03,1);
	x = (i2c_readdata(1)<<8) | (i2c_readdata(0));		//read x_value
	i2c_stop();
	i2c_start();
	i2c_writedata(0x3D,1);
	i2c_writedata(0x04,1);
	z = (i2c_readdata(1)<<8) | (i2c_readdata(0));		//read y_value
	i2c_stop();
	i2c_start();
	i2c_writedata(0x3D,1);
	i2c_writedata(0x05,1);
	y = (i2c_readdata(1)<<8) | (i2c_readdata(0));		//read z_value
	i2c_stop();
	i2c_stop();
}

int main(void)
{
	char data[50],datax[8],datay[8],dataz[8];
	initialize_compass();		//initializing compass
	UART0_init(9600);			//initializing uart
    UART0_writes("initializing compass");
	_delay_ms(3000);
    while (1) 
    {
		_delay_ms(100);
		getdata_compass();		//getting data from compass
		//x = (atan2(y,x)*( 180 / 3.14159265 ) );
		
		dtostrf(x,3,3,datax);			//converting all float values to string
		dtostrf(y,3,3,datay);
		dtostrf(z,3,3,dataz);
		sprintf(data,"X:- %10s \t Y:- %10s \t Z:- %10s\n",datax,datay,dataz); // integrating all datas in one string
		UART0_writes(data);
    }
	return 0;
}

