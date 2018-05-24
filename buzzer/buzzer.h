#ifndef BUZZER_H_
#define BUZZER_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define BUZZER PD4

/* definitii note (Hz) */
#define c    261
#define d    294
#define e    329
#define f    349
#define g    391
#define gS   415
#define a    440
#define aS   455
#define b    466
#define cH   523
#define cSH  554
#define dH   587
#define dSH  622
#define eH   659
#define fH   698
#define fSH  740
#define gH   784
#define gSH  830
#define aH   880


void IO_init(void);

void timer0_init(void);

void timer1_init(void);

void timer2_init(void);
void update_song(void);
void signalBuzzer100(void);
void signalBuzzer200(void);
#endif // BUZZER_H_
