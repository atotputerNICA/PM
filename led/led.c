#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
void signalKey() {
	// led is signaled
	PORTD |= _BV(MOTHER_LED);
	_delay_ms(100);
	PORTD &= ~_BV(MOTHER_LED);
}
void signalGreen() {
	// led is signaled
	PORTA |= _BV(GREEN_LED);
	_delay_ms(100);
	PORTA &= ~_BV(GREEN_LED);

}
void signalRed() {
	// led is signaled
	PORTA |= _BV(RED_LED);
	_delay_ms(100);
	PORTA &= ~_BV(RED_LED);

}
