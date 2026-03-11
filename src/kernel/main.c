#include "hd/millis.h"
#include "hd/delay.h"
#include "hd/sound.h"
#include "card/card.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t last_interrupt;
static volatile uint8_t change_card_flag = 0;

void init_buttons();
void change_card();

void setup_kernel()
{
    last_interrupt = 0;

    init_buttons();
    sound_init();

    card_init();
}

void loop_kernel()
{
    if (change_card_flag)
        change_card();

    card_update();
    sound_update();
}

ISR(INT0_vect)
{
    change_card_flag = 1;
}

void change_card()
{
    static uint32_t last_interrupt = 0;

    uint32_t now = millis1();

    if (now - last_interrupt >= 250)
    {
        card_change();
        last_interrupt = now;
    }

    change_card_flag = 0;
}

void init_isr_button_change_card()
{
    DDRD &= ~(1 << PD2);  // entrada
    PORTD |= (1 << PD2); // pull-up DESLIGADO

    EICRA |= (1 << ISC01);   // falling edge
    EICRA &= ~(1 << ISC00);

    EIMSK |= (1 << INT0);
}

void init_buttons()
{
    init_isr_button_change_card();

    DDRD &= ~(1 << PD3);
    PORTD &= ~(1 << PD3);

    DDRD &= ~(1 << PD4);
    PORTD &= ~(1 << PD4);

    DDRD &= ~(1 << PD5);
    PORTD &= ~(1 << PD5);

    DDRD &= ~(1 << PD6);
    PORTD &= ~(1 << PD6);

    DDRD &= ~(1 << PD7);
    PORTD &= ~(1 << PD7);

    DDRB &= ~(1 << PB0);
    PORTB &= ~(1 << PB0);
}