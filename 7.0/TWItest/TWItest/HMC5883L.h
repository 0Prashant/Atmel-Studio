 #ifndef HMC5883L_H_
   #define HMC5883L_H_

 #include "TWI.h"
 #include <avr/io.h>
 #include "uart.h"
 #include <math.h>
    
 // Register define
 #define kconfig_A  0x00
 #define kconfig_B  0x01
 #define kmode 	    0x02
 #define kmsb_x	    0x03
 #define klsb_x	    0x04
 #define kmsb_y	    0x05
 #define klsb_y	    0x06
 #define kmsb_z	    0x07
 #define klsb_z	    0x08
 #define kstatus    0x09
 #define kid_A	    0x0A
 #define kid_B	    0x0B
 #define kid_C	    0x0C

   #define HMC5883L_WRITE 0x3c // Write address 
   #define HMC5883L_READ 0x3d  // Read address

   int16_t raw_x = 0;
   int16_t raw_y = 0;
   int16_t raw_z = 0;

   
   //  Initialize compass by selecting modes
   void HMC5883L_init(void)
   {

	   twi_init();
	   twi_start(HMC5883L_WRITE);
	   twi_write(kconfig_A);          // Set pointer to CRA
	   twi_write(0x70);               // Write 0x70 to CRA -> Number of samples per output=8, Data output rate = 15Hz
	   twi_stop();

	   twi_start(HMC5883L_WRITE);
	   twi_write(kconfig_B);          // Set pointer to CRB  0x20
	   twi_write(0xA0);               // Gain=390,  Resolution(mg/LSB)=2.56, Output= -2048-2047
	   twi_stop();

	   twi_start(HMC5883L_WRITE);
	   twi_write(kmode);              // Set pointer to measurement mode
	   twi_write(0x00);               // Continous measurement
	   twi_stop();
   }

   // Read raw data of different axes
   void HMC5883L_read(void){

	   twi_start(HMC5883L_WRITE);
	   twi_write(0x03);                //Set pointer to X-axis MSB
	   twi_stop();
	   
	   twi_start(HMC5883L_READ);
	   raw_x = (((uint8_t)twi_read(1)) << 8) | twi_read(1);	// Burst read
	   raw_z = (((uint8_t)twi_read(1)) << 8) | twi_read(1); // Burst read
	   raw_y = (((uint8_t)twi_read(1)) << 8) | twi_read(0);	// Burst read
	   
	   twi_stop();
	   
   }

   // Raw data to angle conversion
   int calculateAngle(){	
   
	//  - Compass heading = atan2(y/x) -> Radian     
	//  - True Heading    = Magnetic Heading + declination Angle -> Radian
	   return ((atan2((double)raw_y,(double)raw_x)* 180 / 3.14159265 + 180.0));
   }

 

 #endif /*COMPASS_H_*/

/******************************************************
             ----REGISTERS AND ADDRESS----
     AdrsLoc     RgstrNme                 Access
        00	Configuration A		Read/Write
        01	Configuration B		Read/Write
        02	Mode			Read/Write
        03	Data Output X MSB	Read
        04	Data Output X LSB	Read
        05	Data Output Z MSB	Read
        06	Data Output Z LSB	Read
        07	Data Output Y MSB	Read
        08	Data Output Y LSB	Read
	09	Status			Read
        10	Identification A	Read
        11	Identification B	Read
        12	Identification C	Read
*******************************************************/