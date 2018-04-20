#ifndef TWI_H
#define TWI_H
#include <math.h>
# define TWBR_value (((F_CPU/frequency)-16)/(2*pow(4,prescalar))
void i2c_initialize(long int frequency, uint8_t prescalar);
void i2c_start();
void i2c_stop();
void i2c_writedata(uint8_t wdata);
uint8_t i2c_readdata(uint8_t ack);

#endif