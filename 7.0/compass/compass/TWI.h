#ifndef F_CPU
 #define F_CPU 16000000UL
#endif /*F_CPU*/

#ifndef TWI_H
 #define TWI_H

void i2c_initialize(long int frequency, uint8_t prescalar);	// for initializing i2c
void i2c_writedata(unsigned char wdata,uint8_t ack);							//for writing data
uint8_t i2c_readdata(uint8_t ack);							//for reading data
void i2c_start();											//for sending start condition
void i2c_stop();											//for sending stop condition

#endif