/*
 * MPU6050.h
 *
 * Created: 2/13/2018 4:39:42 PM
 *  Author: Sherlock
 */

#ifndef _MPU6050_H_
 #define _MPU6050_H_

#define F_CPU 16000000UL		

#include <avr/io.h>		
#include <stdlib.h>		
#include <math.h>
		
 #include "TWI.h"
 #include "UART.h"
 #include "Complementary_Filter.h"

#define PI        3.1415926f
#define HALF_PI   1.5707963f
#define TWO_PI    6.2831853f
#define SQRE(x)   ((x)*(x))


#define MPU6050_READ   0xD1
#define MPU6050_WRITE  0xD0

#define MPU6050_SMPLRT_DIV   0x19
#define MPU6050_CONFIG       0x1A
#define MPU6050_GYRO_CONFIG  0x1B
#define MPU6050_ACCEL_CONFIG 0x1C

#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40
#define MPU6050_TEMP_OUT_H   0x41
#define MPU6050_TEMP_OUT_L   0x42
#define MPU6050_GYRO_XOUT_H  0x43
#define MPU6050_GYRO_XOUT_L  0x44
#define MPU6050_GYRO_YOUT_H  0x45
#define MPU6050_GYRO_YOUT_L  0x46
#define MPU6050_GYRO_ZOUT_H  0x47
#define MPU6050_GYRO_ZOUT_L  0x48

#define MPU6050_INT_PIN_CFG  0x37
#define MPU6050_INT_ENABLE   0x38

#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x01
#define MPU6050_GYRO_FS_1000        0x02
#define MPU6050_GYRO_FS_2000        0x03

#define MPU6050_ACCEL_FS_2          0x00
#define MPU6050_ACCEL_FS_4          0x01
#define MPU6050_ACCEL_FS_8          0x02
#define MPU6050_ACCEL_FS_16         0x03

#define MPU6050_DLPF_BW_256         0x00
#define MPU6050_DLPF_BW_188         0x01
#define MPU6050_DLPF_BW_98          0x02
#define MPU6050_DLPF_BW_42          0x03
#define MPU6050_DLPF_BW_20          0x04
#define MPU6050_DLPF_BW_10          0x05
#define MPU6050_DLPF_BW_5           0x06

#define MPU6050_USER_CTRL        0x6A
#define MPU6050_PWR_MGMT_1       0x6B
#define MPU6050_PWR_MGMT_2       0x6C

#define MPU6050_CLOCK_INTERNAL          0x00
#define MPU6050_CLOCK_PLL_XGYRO         0x01
#define MPU6050_CLOCK_PLL_YGYRO         0x02
#define MPU6050_CLOCK_PLL_ZGYRO         0x03

#define MPU6050_INTMODE_ACTIVEHIGH  0x00
#define MPU6050_INTMODE_ACTIVELOW   0x01

#define MPU6050_INTDRV_PUSHPULL     0x00
#define MPU6050_INTDRV_OPENDRAIN    0x01

#define MPU6050_FIFO_COUNTH      0x72
#define MPU6050_FIFO_COUNTL      0x73
#define MPU6050_FIFO_R_W         0x74

#define MPU6050_WHO_AM_I     0x75

void mpuInitialize();
void getRawData();
void getGyroRate();
void getAccel_gForce();
void getAccelAngle();
float getTemperature();
float formatAccelRange(float accelAngle, float accelZ);


float roll, pitch;

struct accelData
{
	float XAxis;
	float YAxis;
	float ZAxis;
}accelRaw,accel_gForce,accelAngle;

struct gyroData
{
	float XAxis;
	float YAxis;
	float ZAxis;
}gyroRaw,gyroRate;


class mpuConfigure
{
	public:
	void gyroRangeConfig(unsigned char Value);
	void accelRangeConfig(unsigned char value);

}MPU6050config;

float gyroSensitivity;
float accelSensitivity;
float Temperature;

void getRawData()
{
	twi_start(MPU6050_WRITE);
	twi_write(MPU6050_ACCEL_XOUT_H);
	twi_start(MPU6050_READ);


	accelRaw.XAxis = (((int)twi_read(1)<<8) | (int)twi_read(1));
	accelRaw.YAxis = (((int)twi_read(1)<<8) | (int)twi_read(1));
	accelRaw.ZAxis = (((int)twi_read(1)<<8) | (int)twi_read(1));
	Temperature = (((int)twi_read(1)<<8) | (int)twi_read(1));
	gyroRaw.XAxis = (((int)twi_read(1)<<8) | (int)twi_read(1));
	gyroRaw.YAxis = (((int)twi_read(1)<<8) | (int)twi_read(1));
	gyroRaw.ZAxis = (((int)twi_read(1)<<8) | (int)twi_read(0));
	twi_stop();
}

void getGyroRate()
{
	getRawData();
	gyroRate.XAxis = gyroRaw.XAxis/gyroSensitivity;
	gyroRate.YAxis = gyroRaw.YAxis/gyroSensitivity;
	gyroRate.ZAxis = gyroRaw.ZAxis/gyroSensitivity;
}

void getAccel_gForce()
{
	getRawData();
	accel_gForce.XAxis = accelRaw.XAxis/accelSensitivity;
	accel_gForce.YAxis = accelRaw.YAxis/accelSensitivity;
	accel_gForce.ZAxis = accelRaw.ZAxis/accelSensitivity;
}

void getAccelAngle()
{
	getRawData();
	accelAngle.XAxis = 57.295*atan2((float)accelRaw.YAxis,(float)accelRaw.ZAxis);  
	accelAngle.YAxis = 57.295*atan2((float)-accelRaw.XAxis,(float)accelRaw.ZAxis);


}

float formatAccelRange(float AccelAngle, float accelZ)
{
	if(accelZ < 0.0f)
	{
		// Angle lies in Quadrant 2 or Quadrant 3 of
		// the unit circle
		AccelAngle = PI - AccelAngle;
	}
	else if(accelZ > 0.0f && AccelAngle < 0.0f)
	{
		// Angle lies in Quadrant 4 of the unit circle
		AccelAngle = TWO_PI + AccelAngle;
	}

	// If both of the previous conditions were not satisfied, then
	// the angle must lie in Quadrant 1 and nothing more needs
	// to be done.

	return AccelAngle;
}

float getTemperature()
{
	return 	(Temperature/340.00)+36.53;
}


void mpuConfigure::gyroRangeConfig(unsigned char Value)
{
	unsigned char tempRegister = 0x00 ;
	tempRegister |= (Value<<4);

	twi_start(0xD0);
	twi_write(MPU6050_GYRO_CONFIG);
	twi_write(tempRegister);
	twi_stop();

	switch(Value)
	{
		case 0x00: gyroSensitivity = 131; // +-250deg/sec -> 41.667rpm
		break;
		
		case 0x01: gyroSensitivity = 65.5;	//+-500deg/sec -> 83.33rpm
		break;
		
		case 0x02: gyroSensitivity = 32.8;	//+-1000deg/sec -> 166.67rpm
		break;
		
		case 0x03: gyroSensitivity = 16.4;	//+-2000deg/sec -> 333.33rpm
		break;
	}
	//A trade-off between sensitivity and RPM.The unit of sensitivity is LSB/degree/sec.
	//For first case value 131 in the register is 1deg/sec rotation.
}

void mpuConfigure::accelRangeConfig(unsigned char value)
{
	unsigned char tempRegister = 0x00 ;
	tempRegister |= (value<<4);

	twi_start(MPU6050_WRITE);
	twi_write(MPU6050_ACCEL_CONFIG);
	twi_write(tempRegister);
	twi_stop();

	switch (value)
	{
		case 0x00: accelSensitivity = 16384.0;   //+-2g
		break;
		
		case 0x01: accelSensitivity = 8192.0;   //+-4g
		break;

		case 0x02: accelSensitivity = 4096.0;    //+-8g
		break;

		case 0x03: accelSensitivity = 2048.0;    //+-16g
		break;

	}
	//The unit of sensitivity is LSB/g => for first case the value 16384 from register = 1 gravity force !!

}

void mpuInitialize()
{
	twi_start(MPU6050_WRITE);
	twi_write(MPU6050_PWR_MGMT_1);
	twi_write(0x00);
	twi_stop();

	MPU6050config.gyroRangeConfig(3);
	MPU6050config.accelRangeConfig(0);
}


#endif /*_MPU6050_H_*/





