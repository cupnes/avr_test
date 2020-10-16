#define F_CPU	1000000UL	/* 1 MHz */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

__attribute__((noreturn)) int main(void)
{
	cli();

	UBRR0H = 0;
	UBRR0L = 6;	/* 9600 baud @f_osc=1MHz,U2X0=0 */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);	/* Enable receiver and transmitter */
	UCSR0C = 6;	/* async 1 stop bit 8bit char no parity bits */
	_delay_ms(50);

	while (1) {
		while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = 'A';
		_delay_ms(1000);
	}
}

/*
screen /dev/ttyUSB0
or
screen /dev/ttyUSB0 9600,cs8,-parenb,-cstopb
*/
