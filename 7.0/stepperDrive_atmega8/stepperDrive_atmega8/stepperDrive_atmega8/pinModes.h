/*
 * pinModes.h
 *
 * Created: 2/8/2018 7:50:56 PM
 *  Author: Sherlock
 */


#ifndef PINMODES_H_
#define PINMODES_H_


// Data direction
#define kinput(kPORT,kPIN) DDR ## kPORT &= ~_BV(kPIN)     // ## -> Token concatenation
#define koutput(kPORT,kPIN) DDR ## kPORT |= _BV(kPIN)      // bitValue: _BV(Num) => (1<<Num)

//PIN condition
#define kclear(kPORT,kPIN) PORT ## kPORT &= ~_BV(kPIN)
#define kset(kPORT,kPIN) PORT ## kPORT |= _BV(kPIN)
#define ktoggle(kPORT,kPIN) PORT ## kPORT ^= _BV(kPIN)


//Single argument
#define INPUT(x)  kinput(x)
#define OUTPUT(x) koutput(x)
#define CLEAR(x)  kclear(x)
#define SET(x)	  kset(x)
#define TOGGLE(x) ktoggle(x)

#define PULLUP(x)          INPUT(x); SET(x)
#define PULLUP_OFF(x)      INPUT(x); CLEAR(x)

#include <avr/io.h>


#endif /* PINMODES_H_ */