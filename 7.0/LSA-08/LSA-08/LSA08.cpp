/*
 * LSA08.cpp
 *
 * Created: 12/25/2017 2:48:52 PM
 *  Author: Rishav
 */

#include <avr/io.h>
#include "LSA08.h"

void LSA08_init(int manualSet, int modeSel, int baudRate){

	LSA08_sendCommand('D',kdataMode);	            // Uart_data output mode select
	LSA08_sendCommand('R',kbaudRate);
	if (manualSet == 1)
	{
	  LSA08_sendCommand('L',kmode);
	  LSA08_sendCommand('T',kthreshold);
	  LSA08_sendCommand('J',kjwidth);
	  LSA08_sendCommand('B',klcd_backLight);
	  LSA08_sendCommand('X',kjuncInfo);
	  //LSA08_sendCommand('P',kline);

	}

}

void LSA08_sendCommand(char COMMAND, char DATA){


	char CHECKSUM = kuartAddress + COMMAND + DATA;

	uartPuts(kuartAddress);
	uartPuts(COMMAND);
	uartPuts(DATA);
	uartPuts(CHECKSUM);

	// 	if (uart0_gets()=="OK"){
	//
	// 		// Display Success Message
	// 	}
	// 	else{
	// 		 // Display Failure Message
	// 	}

}

uint8_t LSA08_readValue(char command,char data){

	char CHECKSUM = kuartAddress + COMMAND + DATA;

	uartPuts(kuartAddress);
	uartPuts(COMMAND);
	uartPuts(DATA);
	uartPuts(CHECKSUM);

	PORTUEN
	while(uart0_available()){

	 return uart0_getc()

	}



}