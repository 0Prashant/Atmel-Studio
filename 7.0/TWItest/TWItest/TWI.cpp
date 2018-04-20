/*
 * TWI.cpp
 *
 * Created: 10/24/2017 12:21:24 AM
 * Author : Rishav
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include "TWI.h"


void twi_init(void)
{
        TWBR = ktwbr_val ;                                    // Bit-rate for clock frequency
	TWSR = (0 << TWPS1) | (0<<TWPS0) ;                    // Pre-scale set to 1
	TWCR = (1 << TWEN) |
 	       (0 << TWEA) |  (0 << TWSTA) | (0 << TWSTO) ;   // No signal request
	
}/*twi_init*/


/*
 * Sets start condition and sends address  
 */
void twi_start(uint8_t address)
{

   
	TWCR = 	(1 << TWEN)  |				      //  Activate the TWI interface.
		(1 << TWINT) |                                //  Clear the interrupt flag
	        (0 << TWEA)  | (1 << TWSTA) | (0 << TWSTO);   //  Check the bus and generate START condition if bus is free.
	                                     
	while (!(TWCR & (1<<TWINT)));                         // Wait for end of transmission
	
	if(((kTWstatus & 0xF8) != kstart) && ((kTWstatus & 0xF8) != krep_start)) twi_error();	// Check 'Start Condition' transmission (Reset: 0xF8)
	TWDR = address ;                                      // Loads slave address once start condition transmitted    
	
	TWCR = (1<<TWINT)|(1<<TWEN);                          // Clear flag set during completion of above transmission  
	 					    
	while(!(TWCR & (1<<TWINT)));			      // Wait for end of transmission
	 	if (((kTWstatus & 0xF8) != kslave_addr) && ((kTWstatus & 0xF8) !=ksalve_addw )) twi_error();  //Check TWSR ifslave has acknowledged R/W mode 
}/*twi_start*/

/*
* Generates stop condition
*/
void twi_stop(void)
{
	TWCR = (1 << TWEN)  |                               // Enable TWI interface
	       (1 << TWINT) |                               // Clear Interrupt flag 
	       (0 << TWEA)  | (0 << TWSTA) | (1 << TWSTO);  // Generate STOP condition
	
	while(TWCR & (1<<TWSTO));
}


 /*
  * Reads data from addressed device
  * Returns : Read data
  */
unsigned char twi_read(unsigned char ack)
{      
		TWCR = (1 << TWEN)  |                          // Start TWI
		       (1 << TWINT) |                                 // Clear interrupt flag
		      (ack << TWEA) | (0 << TWSTA) | (0 << TWSTO);  //  Acknowledge data on reception	if ack =1 else do not acknowledge

	
	while (!(TWCR & (1<<TWINT)));           // Wait until data is read
	return TWDR;                            // Return received data

}


/*
 *  Send data to previously addressed device  
 */
void twi_write( uint8_t value )
{	
	TWDR = value;                                 // Load data to TWDR to send to the addressed device
	TWCR = (1<<TWINT) | (1<<TWEN);                // Clear TWINT bit in TWCR to start transmission of data

        while(!(TWCR & (1<<TWINT)));	              // Wait for TWINT flag set i.e. until transmission completed

	if( (kTWstatus & 0xF8) != kdata) twi_error(); // If status different from data_ack, error();
	
}

unsigned char twi_error(void)
{
	return 1;
}








