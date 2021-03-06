/*
 * uart.c
 *
 * Created: 5P � � �	                                                                                                                        1 0 1 2 3 0 6 4 0 0 9 3 4 6                                                 
    @ 	   ��	  P �@ �@ � � smi                                              ( � ?�(2            0P         !! H  �                "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  0P     );
	
	//set frame format
	UCSR3C= ((1<<UCSZ30)|(1<<UCSZ31));
}

void UART0Transmit(unsigned char data)
{
	//wait for transmit buffer to be empty
	while(!((UCSR0A)&(1<<UDRE0)));
	
	//send data
	UDR0=data;
}


void UART1Transmit(unsigned char data)
{
	//wait for transmit buffer to be empty
	while(!((UCSR1A)&(1<<UDRE1)));
	
	//send data
	UDR1=data;
}


void UART2Transmit(unsigned char data)
{
	//wait for transmit buffer to be empty
	while(!((UCSR2A)&(1<<UDRE2)));
	
	//send data
	UDR2=data;
}
void UART3Transmit(unsigned char data)
{
	//wait for transmit buffer to be empty
	while(!((UCSR3A)&(1<<UDRE3)));
	
	//send data
	UDR3=data;
}



unsigned char UART0Receive(void)
{
	char data=buffer;
	buffer=0;
	return data;
}

unsigned char UART1Receive(void)
{
	char data=buffer1;
	buffer1=0;
	return data;
}


unsigned char UART2Receive(void)
{
	char data=buffer2;
	buffer2=0;
	return data;
}

unsigned char UART3Receive(void)
{
	char data=buffer3;
	buffer3=0;
	return data;
}

void UART0TransmitData(int data)
{
	char buffer[20];
	char *i=0;
	itoa(data,buffer,10);
	i=buffer;
	while(*i)
		UART0Transmit(*i++);
}

void UART1TransmitData(int data)
{
	char buffer[20];
	char *i=0;
	itoa(data,buffer,10);
	i=buffer;
	while(*i)
	UART1Transmit(*i++);
}

void UART2TransmitData(int data)
{
	char buffer[20];
	char *i=0;
	itoa(data,buffer,10);
	i=buffer;
	while(*i)
	UART2Transmit(*i++);
}

void UART3TransmitData(int data)
{
	char buffer[20];
	char *i=0;
	itoa(data,buffer,10);
	i=buffer;
	while(*i)
	UART3Transmit(*i++);
}


void UART0TransmitString(const char *s)
{
	while(*s)
		UART0Transmit(*s++);
}

void UART1TransmitString(const char *s)
{
	while(*s)
	UART1Transmit(*s++);
}


void UART2TransmitString(const char *s)
{
	while(*s)
	UART2Transmit(*s++);
}

void UART3TransmitString(const char *s)
{
	while(*s)
	UART3Transmit(*s++);
}

ISR(USART0_RX_vect)
{
	buffer=UDR0;
}

ISR(USART1_RX_vect)
{
	buffer1=UDR1;
	
}

ISR(USART2_RX_vect)
{
	buffer2=UDR2;
}
ISR(USART3_RX_vect)
{
	buffer3=UDR3;
}
