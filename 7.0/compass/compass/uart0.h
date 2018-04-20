/*
 * uart0.h
 *
 * Created: 9/19/2017 3:59:50 AM
 *  Author: n-is
 */

/*
 * Pins Occupied :
 *	RX and TX pin
 */


#ifndef UART0_H_
#define UART0_H_

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU		16000000
#endif

#define UBR0(baud)	((F_CPU / 16 / baud) - 1)

#define TX0_BUF_SIZE		32
#define RX0_BUF_SIZE		32


extern int8_t UART0_init(uint16_t baud_rate);
// extern void UART0_transmitt(const uint8_t data);
// extern uint8_t UART0_receive( void );

extern void UART0_write(const uint8_t data);
extern void UART0_writes(const char *str);
extern uint8_t UART0_read( void );

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* UART0_H_ */