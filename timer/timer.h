#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <util/delay.h>

void setTimerCount(int value);

void setTimer();

void disableTimer();

#endif // TIMER_H_
