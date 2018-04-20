/*
 * TWI.h
 *
 * Created: 10/24/2017 12:22:45 AM
 * Author : Rishav
 */ 

#ifndef  TWI_H_
 #define TWI_H_

 #ifndef F_CPU
  #define F_CPU        16000000UL
 #endif

// Change clock and prescale parameters as required		   
#define ktwi_clk       100000UL
#define ktwi_prescale  1

#define ktwbr_val      ((((F_CPU/ktwi_clk)/ktwi_prescale)-16)/2)

#define kTWstatusMask  ((1 << TWS7)|(1 << TWS6)|(1 <<TWS5)|(1 << TWS4)|(1 << TWS3))  // Two LSB are not TWstatus bits but pre-scalar bits
#define kTWstatus      (kTWstatusMask & TWSR)				             // TWSR is masked by kstatusMask 

// Conditions and corresponding value of TWI status registers
#define kstart        0x08    // Start condition transmitted
#define ksalve_addw   0x18    // SLA+W transmitted, ACK received
#define kslave_addr   0x40    // SLA+R transmitted, ACK received
#define kdata         0x28    // Data transmitted, ACK received
#define krep_start    0x10    // Repeated start condition transmitted

void twi_init(void);
void twi_stop(void);
void twi_start(uint8_t address);
void twi_write( uint8_t value );
unsigned char twi_read(unsigned char ack);
unsigned char twi_error(void);

#endif /* twi.h */

/* ----------------------------------------------------- REGISTERS -------------------------------------------------------------------*
 *							~~~~~~~~~~~							              *
 * TWBR : Selects the division factor to control SCL clock frequency								      *
 *	  {{SCL frequency = (CPU clock frequency)/(16 + 2*(TWBR)*4^TWPS)}} 							      *
 * TWSR : Shows the status of TWI logic and bus.										      *
 *          As first two bits are prescalar bits they need to be masked to read TWI status					      *
 * TWCR : Controls operation of the TWI	 -> TWINT, TWEA, TWSTA, TWSTO, TWWC, TWEN and TWIE					      *
 * TWDR : In recieve mode it contains last recieved byte and in transmit mode it holds last transmitted byte 			      *
 * TWAR : 7 bit slave address to which the TWI will respond when working as slave 						      *
 * 																      *
 * ----------------------------------------------------- HAND OUTS -------------------------------------------------------------------*
 *							~~~~~~~~~~~								      *
 * - TWINT is set by hardware when TWI module has finished its current job.							      *
 * - While TWINT Flag is set, the SCL low period is stretched, and (1<<TWINT): clears the flag.					      *
 * - For TWSR, the status 0xF8 indicates that no relevant information is available because the TWINT Flag is not set.		      *
 *   This occurs between other states, and when the TWI is not involved in a serial transfer					      *
 * - The TWINT Flag is set in the following situations:										      *
 *		• After the TWI has transmitted a START/REPEATED START condition.						      *
 *		• After the TWI has transmitted SLA+R/W.									      *
 *		• After the TWI has transmitted an address byte.								      *
 *		• After the TWI has lost arbitration.										      *
 *		• After the TWI has been addressed by own slave address or general call.					      *
 *		• After the TWI has received a data byte.									      *
 *		• After a STOP or REPEATED START has been received while still addressed as a Slave.				      *
 *		• When a bus error has occurred due to an illegal START or STOP condition.					      *
 * 					 											      *
 *						        ***									      *
 *------------------------------------------------------------------------------------------------------------------------------------*/
 																      