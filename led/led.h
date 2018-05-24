#ifndef LED_H_
#define LED_H_

#include <avr/io.h>
#include <util/delay.h>

#define GREEN_LED PA2
#define RED_LED	PA1
#define MOTHER_LED PD7


void signalKey();
void signalGreen();
void signalRed();

#endif // LED_H_
