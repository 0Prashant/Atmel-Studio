/*
 * mpu6050.c
 *
 * Created: 11/26/2017 1:04:48 AM
 * Author : Prashant
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*#include <util/twi.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "uart.h"
#include "TWI.h"

float ax,ay,az,gx,gy,gz,t;

void init6050()
{   
	i2c_initialize(50000,0);
	i2c_start();
	i2c_writedata(0xD0);	// CONFIG mpu6050
	i2c_writedata(0x6B);
	i2c_writedata(0x00);
	i2c_stop();
	i2c_start();
	i2c_writedata(0b1101000);	//set accelerometer range
	i2c_writedata(0x1B);
	i2c_writedata(0x00);
	i2c_writedata(0X18);
	i2c_stop();
	i2c_start();
	i2c_writedata(0b1101000);		//set gyroscope range
	i2c_writedata(0x38);		
	i2c_writedata(0x01);
	i2c_stop();
}
void get_data(float *ax, float *ay,float *az, float *gx, float *gy,float *gz, float *t)
{
	i2c_start();
	i2c_writedata(0xD1);		//send address of slave with read mode
	i2c_writedata(0x3B);		//point to address 3B for reading accelerometer data
	*ax = ~(((i2c_readdata(1)<<8) | (i2c_readdata(1)))-1);
	*ay = ~(((i2c_readdata(1)<<8) | (i2c_readdata(1)))-1);
	*az = ~(((i2c_readdata(1)<<8) | (i2c_readdata(1)))-1);
	*t  = ~(((i2c_readdata(1)<<8) | (i2c_readdata(1)))-1);
	*gx = ~(((i2c_readdata(1)<<8) | (i2c_readdata(1)))-1);
	*gy = ~(((i2c_readdata(1)<<8) | (i2c_readdata(1)))-1);
	*gz = ~(((i2c_readdata(1)<<8) | (i2c_readdata(0)))-1);
	i2c_stop();
}


void send_data(float ax,float ay,float az,float gx,float gy,float gz,float t)
{
	char data[50];
	char data_ax[7],data_ay[7],data_az[7],data_gx[7],data_gy[7],data_gz[7],data_t[7];
	dtostrf(ax,3,2,data_ax);
	dtostrf(ay,3,2,data_ay);
	dtostrf(az,3,2,data_az);
	dtostrf(gx,3,2,data_gx);
	dtostrf(gy,3,2,data_gy);
	dtostrf(gz,3,2,data_gz);
	dtostrf(t,3,2,data_t);
	sprintf (data,"Ax:-%s\tAy:-%s\tAz:-%sGx:-%s\tGy:-%s\tGz:-%s\tT:-%s",data_ax,data_ay,data_az,data_gx,data_gy,data_gz,data_t);
	uart_puts(data);
}
int main(void)
{
	_delay_ms(150);
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	init6050();
	_delay_ms(150);
	while (1)
	{
		get_data(&ax,&ay,&az,&gx,&gy,&gz,&t);
		send_data(ax,ay,az,gx,gy,gz,t);
	}
	return 0;
}




