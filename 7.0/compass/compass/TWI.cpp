#include <avr/io.h>
#include <math.h>
#include <inttypes.h>
#include <stdlib.h>
//#include <util/twi.h>
#include "TWI.h"

void i2c_initialize(long int frequency, uint8_t prescalar)
{
	TWCR = (1<<TWEN);				//this enables twi interface
	TWSR = prescalar;				//initialize i2c bus by using prescalar (see TWSR register)
	uint8_t TWBR_value = (((F_CPU/frequency)-16)/(2*pow(4,prescalar)));	//setting values to TWBR
	TWBR = TWBR_value;	
}

void i2c_start()
{ 
	TWCR =  (0 << TWEA)  | (1 << TWSTA) | (0 << TWSTO) | (1<<TWINT) | (1<<TWEN); //send start condition and always enable TWEN (also TWINT for next step) 
	while (!(TWCR & (1<<TWINT)));				//wait till task not finished
}

void i2c_stop()
{
	TWCR = (1<<TWSTO) |(0 << TWEA)  | (0 << TWSTA) | (1<<TWINT) | (1<<TWEN);	//send stop condition and always enable TWEN (also TWINT for next step)
}

void i2c_writedata(unsigned char wdata,uint8_t ack)
{
	TWDR = wdata;							// sending data
	TWCR =  (1<<TWINT) | (1<<TWEN) | ack << TWEA;			//always enable TWEN (also TWINT for next step)
	while (!(TWCR & (1<<TWINT)));			//wait till task not finished
}

unsigned char i2c_readdata(unsigned char ack)
{
	TWCR =  (1<<TWINT) | (1<<TWEN) | ack <<TWEA | (0 << TWSTA) | (0 << TWSTO);//always enable TWEN (also TWINT for next step) and sending ack or nack condition
	while (!(TWCR & (1<<TWINT)));				//wait till task not finished
	return TWDR;								// returning the recieved data
}