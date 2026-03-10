#include "hd/millis.h"
#include "hd/delay.h"
#include "card/card.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void check_change_button_card();
void init_buttons();

void setup_kernel()
{
    init_buttons();

    card_init();
}

void loop_kernel()
{
    check_change_button_card();    
    card_update();
}

void check_change_button_card()
{
    if (PIND & (1 << PD2))
    {
        card_change();
        delay(250);
    }
}

void init_buttons() {
    DDRD  &= ~(1 << PD2);  // entrada
    PORTD &= ~(1 << PD2); // pull-up DESLIGADO

    DDRD  &= ~(1 << PD3);
    PORTD &= ~(1 << PD3);

    DDRD  &= ~(1 << PD4);
    PORTD &= ~(1 << PD4);

    DDRD  &= ~(1 << PD5);
    PORTD &= ~(1 << PD5);

    DDRD  &= ~(1 << PD6);
    PORTD &= ~(1 << PD6);

    DDRD  &= ~(1 << PD7);
    PORTD &= ~(1 << PD7);

    DDRB  &= ~(1 << PB0);
    PORTB &= ~(1 << PB0);
}