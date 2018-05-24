/*
 * Nica Dana-Maria 334CA
 * ALARM SYSTEM
 */

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "lcd/lcd.h"
#include "keypad/key.h"
#include "buzzer/buzzer.h"
#include "led/led.h"
#include "timer/timer.h"
#define START 'A'
#define NOT_ARMED 0
#define INTRUDER 1
#define ARMED 2
#define GET_OUT_MOTHERFUCKER 3

#define DELETE 68
#define ACCEPT 35

#define BUZZER PD4
#define BUZZER2 PA0
#define GREEN_LED PA2
#define RED_LED	PA1
#define MOTHER_LED PD7
#define TRIGGER_PIN PD3
#define ECHO_PIN PD5

#define TRUE 1
#define FALSE 0

#define SIGNAL_DIST 30

#define TIMEOUT1 20 // 10 secunde

// keyboard (int)
int keyboard[4][4] = {
	{1, 4, 7, 42},
	{2, 5, 8, 0},
	{3, 6,9, 35},
	{65, 66, 67, 68}
};

int pos = 0;

int state = NOT_ARMED, alarmCode = 0, insertedCode = 0;
int nrRounds;
volatile int computeDist = FALSE;
int distStarted;

const int timerLimit = 15;
int timerCnt = 0;

void checkKey(int curState) {
	int row = -1, col = -1;
	if (GetKeyPressed(&row, &col) == 1) {
		if (keyboard[row][col] == DELETE) {
			// Delete last pressed key
			signalKey();
			insertedCode /= 10;
			pos--;
			LCD_putCharAt(pos, ' ');
		} else if (keyboard[row][col] == ACCEPT) {
			if (insertedCode == alarmCode) {
				// Correct PASSWORD
				if (state == GET_OUT_MOTHERFUCKER) {
					disableTimer();
				}
				state = NOT_ARMED;
				PORTD |= (_BV(BUZZER));
				PORTD &= ~(_BV(MOTHER_LED));
				LCD_printMessage("NOT ARMED");
				signalGreen();
				alarmCode = 0;
				insertedCode = 0;
			} else {
				insertedCode = 0;
			}
		} else {
			// Add pressed key value
			insertedCode = insertedCode * 10 + keyboard[row][col];
			signalKey();
			if (pos == 0)
				LCD_writeInstr(LCD_INSTR_clearDisplay);
			LCD_printAt(pos, "*");
			pos++;

		}

		for (; GetKeyPressed(&row, &col) == 1; ) {
			// cycle whille key pressed and the state is not changed
			if (curState != state && state != NOT_ARMED) {
				break;
			}
		}
	}
}


ISR(TIMER0_COMPA_vect) {
	cli();

	if (computeDist == TRUE) {
		if ((PIND & _BV(ECHO_PIN)) > 0) {
			// increment number of rounds
			distStarted = TRUE;
			nrRounds++;
		} else if (distStarted == TRUE) {
			// end of data reception
			computeDist = FALSE;
		}
	}

	sei();
}

ISR(TIMER1_COMPA_vect) {
	cli();
	if (state == INTRUDER) {
		timerCnt++;
		// BUZZER sound
		signalBuzzer100();

		if (timerCnt == timerLimit) {
			disableTimer();
			if (state == INTRUDER) {
				state = GET_OUT_MOTHERFUCKER;
				insertedCode = 0;
				LCD_printMessage("ALARM!!");
				signalBuzzer100();
			}
		}
	} else if (state == GET_OUT_MOTHERFUCKER) {
		// Activam un clipit al LCD-ului
		LCD_printMessage("ALARM!!");
		_delay_ms(200);
		LCD_writeInstr(LCD_INSTR_clearDisplay);
		signalBuzzer100();
	}

	sei();
}


int checkDist() {
	if (computeDist == FALSE) {
		// Send a signal to TRIGGER and wait
		nrRounds = 0;
		PORTD |= _BV(TRIGGER_PIN);
		_delay_us(20);
		PORTD &= ~_BV(TRIGGER_PIN);
		distStarted = FALSE;
		computeDist = TRUE;
	}

	while (computeDist == TRUE);

	return nrRounds <= SIGNAL_DIST;
}

void startINTRUDER() {
	state = INTRUDER;
	LCD_printMessage("INTRUDER");
	PORTD &= ~_BV(MOTHER_LED);
	signalRed();
	setTimerCount(F_CPU / 256);
}


int main(){

	DDRD = _BV(MOTHER_LED) | _BV(BUZZER) ;
	DDRA |= _BV(GREEN_LED) | _BV(RED_LED);
  DDRC |= (1 << PC2);
  PORTC |= (1 << PC2);
	int i = 0;
 	PORTD |= _BV(BUZZER);


	LCD_init();
	LCD_printAt(0, "PM2018");
	LCD_writeInstr(LCD_INSTR_clearDisplay);


	while(1) {
	// 	update_song();
		//LCD_writeInstr(LCD_INSTR_clearDisplay);
		LCD_printAt(0, "atotputerNICA");
		int row = -1, col = -1;
		if (GetKeyPressed(&row, &col) == 1) {
			if (keyboard[row][col] == START) {
				signalKey();
				LCD_writeInstr(LCD_INSTR_clearDisplay);
				break;
			}
			// cycle whille key pressed
			for (; GetKeyPressed(&row, &col) == 1; );
		}

	}
	LCD_init();
	sei();

	// interrupt
	TIMSK0 |= _BV(OCIE0A);

	TCCR0B |= (1 << WGM01);
	TCCR0B |= (1 << CS01);

	OCR0A = 160; // 10 usecunde

  LCD_writeInstr(LCD_INSTR_clearDisplay);
  LCD_printAt(0,"NOT ARMED");

	PORTD = 0;
 	PORTD |= _BV(BUZZER);
	_delay_ms(100);
	while (1) {

		switch(state) {


			case NOT_ARMED: {
				int row = -1, col = -1;
				if (GetKeyPressed(&row, &col) == 1) {
					if (keyboard[row][col] == DELETE) {
						// Delete last key pressed
						alarmCode /= 10;
						pos--;
						LCD_putCharAt(pos, ' ');
						signalKey();

					} else if (keyboard[row][col] == ACCEPT) {
						// TO ARMED and setTimer
						state = ARMED;
						setTimer();
						LCD_printMessage("ARMED");
						for (i = 0; i < TIMEOUT1; i++) {
							signalKey();
							signalGreen();
							_delay_ms(50);
						}
					} else {
						// Add pressed key value
						alarmCode = alarmCode * 10 + keyboard[row][col];
						signalKey();
						// LCD_putCharAt(LCD_INSTR_nextLine,keyboard[row][col]);
						if (pos == 0)
							LCD_writeInstr(LCD_INSTR_clearDisplay);
						LCD_printAt(pos, "*");
						pos++;

					}
					// cycle whille key pressed
					for (; GetKeyPressed(&row, &col) == 1; );
				}
				break;
			}


			case ARMED: {

				PORTD &= ~_BV(MOTHER_LED);
				checkKey(ARMED);
				pos = 0;
				if (checkDist()) {
					startINTRUDER();
				}

				break;
			}


			case INTRUDER: {
				checkKey(INTRUDER);

				break;
			}

			case GET_OUT_MOTHERFUCKER: {
				signalBuzzer200();
				signalRed();
				//checkKey(GET_OUT_MOTHERFUCKER);

				break;
			}

		}
	}

	return 0;
}
