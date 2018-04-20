#include <avr/io.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
#include "TWI.h"

void i2c_initialize(long int frequency, uint8_t prescalar)
{
	TWCR = (1<<TWEN);
	TWSR = prescalar;
	long int TWBR_value = (((F_CPU/frequency)-16)/(2*pow(4,prescalar)));
	TWBR = TWBR_value;
	
}

void i2c_start()
{
	TWCR = (1<<TWSTA) | (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void i2c_stop()
{
	TWCR = (1<<TWSTO) | (1<<TWINT) | (1<<TWEN);
}

void i2c_writedata(unsigned char wdata)
{
	TWDR = wdata;
	TWCR =  (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

unsigned char i2c_readdata(unsigned char ack)
{
	TWCR =  (1<<TWINT) | (1<<TWEN) | ack <<TWEA;
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}