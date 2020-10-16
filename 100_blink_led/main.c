#define F_CPU	1000000UL	/* 1 MHz */
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

__attribute__((noreturn)) int main(void)
{
	cli();

	DDRC = _BV(PC0);

	while (1) {
		PORTC |= _BV(PORTC0);
		_delay_ms(1000);
		PORTC &= ~_BV(PORTC0);
		_delay_ms(1000);
	}
}
