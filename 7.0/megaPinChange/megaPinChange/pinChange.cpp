/*
 * pinChange.cpp
 *
 * Created: 1/9/2018 12:26:51 AM
 *  Author: Sherlock
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pinChange.h"

/******************************************************
Available functions:

pinChangeZero_init() ->
	Initializes (enables) the pinchange change interrupt pins 0:7
pinChangeOne_init() ->
	Enables the pinchange change interrupt pins 8:15
pinChangeOne_init() ->
	Enables the pinchange change interrupt pins 16:23
	Any change on any enabled PCINTx:y pin will cause an interrupt.
setPin(int pinChange_number,int PinNumber) -> Enable each individual pin
	PinChange_numbers: 0,1 and 2 selects among 0:7, 8:15, and 16:23
	PinNumber : Selects specific pin.

CHART: PinNumber and real pinConfiguration

| PCINT |   Mega/2560    |
| ----- | -------------- |
|     0 | 53 SS   (PB0)  |
|     1 | 52 SCK  (PB1)  |
|     2 | 51 MOSI (PB2)  |
|     3 | 50 MISO (PB3)  |
|     4 | 10      (PB4)  |
|     5 | 11      (PB5)  |
|     6 | 12      (PB6)  |
|     7 | 13      (PB7)  |
| ----- | -------------- |
|     8 |  0 RX   (PE0)* |
|     9 | 15 RX3  (PJ0)* |
|    10 | 14 TX3  (PJ1)* |
|    11 |    NC   (PJ2)* |
|    12 |    NC   (PJ3)* |
|    13 |    NC   (PJ4)* |
|    14 |    NC   (PJ5)* |
|    15 |    NC   (PJ6)* |
| ----- | -------------- |
|    16 | A8      (PK0)  |
|    17 | A9      (PK1)  |
|    18 | A10     (PK2)  |
|    19 | A11     (PK3)  |
|    20 | A12     (PK4)  |
|    21 | A13     (PK5)  |
|    22 | A14     (PK6)  |
|    23 | A15     (PK7)	 |


******************************************************/
void pinChangeZero_init(){

	PCICR |= (1<<PCIE0);
}

void pinChangeOne_init(){

	PCICR |= (1<<PCIE1);
}

void pinChangeTwo_init(){

	PCICR |= (1<<PCIE2);
}

void setPin(int pinChange_number,int PinNumber){

	if (!pinChange_number)
	{
		PCMSK0 |= (1<<PinNumber);
	}

	if (pinChange_number == 1)
	{
		PinNumber -= 8;
		PCMSK1 |= (1<<PinNumber);
	}
	if (pinChange_number == 2)
	{
		PinNumber -= 16;
		PCMSK2 |= (1<<PinNumber);
	}
}
