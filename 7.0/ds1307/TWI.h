#ifndef _TWI_
#define _TWI_
# define TWBR_value (((F_CPU/frequency)-16)/(2*pow(4,prescalar))

void i2c_initialize(long int frequency, uint8_t prescalar);
void i2c_start();
void i2c_stop();
void i2c_writedata(unsigned char wdata);
unsigned char i2c_readdata(unsigned char ack);

#endif /*TWI_H*/