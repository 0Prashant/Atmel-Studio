#ifndef F_CPU
 #define F_CPU 16000000UL
#endif /*F_CPU*/

#ifndef TWI_H
 #define TWI_H

void i2c_initialize(long int frequency, uint8_t prescalar);
void i2c_writedata(uint8_t wdata);
uint8_t i2c_readdata(uint8_t ack);
void i2c_start();
void i2c_stop();

#endif