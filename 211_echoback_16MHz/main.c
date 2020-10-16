#define F_CPU	16000000UL	/* 16 MHz */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

__attribute__((noreturn)) int main(void)
{
	cli();

	UBRR0H = 0;
	UBRR0L = 103;	/* 9600 baud @f_osc=16MHz,U2X0=0 */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);	/* Enable receiver and transmitter */
	UCSR0C = 6;	/* async 1 stop bit 8bit char no parity bits */
	_delay_ms(50);

	while (1) {
		unsigned char c;

		/* Wait for data to be received */
		while (!(UCSR0A & (1 << RXC0)));
		c = UDR0;

		/* Wait for empty transmit buffer */
		while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = c;
	}
}

/*
screen /dev/ttyUSB0
or
screen /dev/ttyUSB0 9600,cs8,-parenb,-cstopb
*/
