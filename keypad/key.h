#ifndef KEY_H_
#define KEY_H_

#include <avr/io.h>
#include <util/delay.h>
#define KEYPAD_PORT PORTB
#define KEYPAD_DDR   DDRB
#define KEYPAD_PIN   PINB

int GetKeyPressed(int *row, int *col);
#endif // KEY_H_
