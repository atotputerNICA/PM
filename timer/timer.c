#include <avr/io.h>
#include <util/delay.h>
#include "timer.h"
void setTimerCount(int value) {
	OCR1A = value;
}

void setTimer() {
	// Initiem timerul 1 - cel pentru sunetul de alarma
	//timerCnt = 0;

	TIMSK1 |= _BV(OCIE1A);

	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12);

	setTimerCount(F_CPU / 256 / 5);
}

void disableTimer() {
	TIMSK1 &= ~(_BV(OCIE1A));

	TCCR1B &= ~(1 << WGM12);
	TCCR1B &= ~(1 << CS12);
}
