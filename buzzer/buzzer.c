#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "buzzer.h"
uint16_t surprise_notes[] = {a, a, a, f, cH, a, f, cH, a, eH, eH, eH, fH, cH, gS, f, cH, a, aH, a, a, aH, gSH, gH, fSH, fH, fSH, aS, dSH, dH, cSH, cH, b, cH, f, gS, f, a, cH, a, cH, eH, aH, a, a, aH, gSH, gH, fSH, fH, fSH, aS, dSH, dH, cSH, cH, b, cH, f, gS, f, cH, a, f, cH, a};

uint16_t durations[] = {500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 500, 500, 350, 150, 500, 350, 150, 650, 500, 300, 150, 400, 200, 200, 125, 125, 250, 250, 400, 200, 200, 125, 125, 250, 125, 500, 375, 125, 500, 375, 125, 650, 500, 300, 150, 400, 200, 200, 125, 125, 250, 250, 400, 200, 200, 125, 125, 250, 250, 500, 375, 125, 500, 375, 125, 650};

uint8_t num_notes = sizeof(durations) / sizeof(durations[0]);
void IO_init(void)
{
    /* speaker-ul este pus ca iesire */
    DDRD |= (1 << PD4) ;
}

void timer0_init(void)
{
    TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1) | (1 << COM0A0);
    OCR0A = 0xC0;
    TCCR0B |= (1 << CS00);
}

void timer1_init(void)
{
#if 0
    /* timer1 este configurat cu modul Normal, top 0xFFFF si prescaler 256 */
    TCCR1B |= (1 << CS12);
#endif
    TCCR1B |= (1 << CS10);
#if 0
    TIMSK1 |= (1 << OCIE1A) | (1 << TOIE1);
#endif
    /* Task2 */
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0);

#if 0
    /* Task1 */
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13);
#endif

#if 0
    /* 16MHz / 256 = 62500 Hz */
    ICR1 = 62500;
#endif
    ICR1 = 0xFFFF;

    /* Task6 */
    TCCR1A |= (1 << COM1B1) | (1 << WGM10) | (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS12);
#if 0
    /* duty cycle-ul este setat initial la 25% */
    OCR1A = 0xFFFF / 4;
    /* duty cycle-ul initial pentru speaker (OC1B) este 50% */
    OCR1B = 0xFFFF / 2;
#endif
    /* Task 1 */
    OCR1A = ICR1 / 4;
    OCR1B = ICR1 / 2;
}

void timer2_init(void)
{
    TCCR2A |= (1 << WGM21) | (1 << WGM20) | (1 << COM2A1) | (1 << COM2A0);
#if 0
    OCR2A = 0xC0;
#endif
    TCCR2B |= (1 << CS20);
}

int nr_nota;
int durata;
void update_song(void)
{
    durata -= 25;
    if (durata < 25) {
        OCR1A = 15625 / surprise_notes[nr_nota];
        OCR1B = OCR1A/2;
        TCNT1 = 0;
        durata = durations[nr_nota];
        nr_nota = (nr_nota+1)%64;
    }
}

void signalBuzzer100(void) {
  PORTD &= ~_BV(BUZZER);
  _delay_ms(100);
  PORTD |= _BV(BUZZER);
  _delay_ms(100);
}

void signalBuzzer200(void) {
  PORTD &= ~_BV(BUZZER);
  _delay_ms(200);
  PORTD |= _BV(BUZZER);
  _delay_ms(200);
}
