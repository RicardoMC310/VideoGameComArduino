#include "hd/millis.h"
#include "hd/delay.h"
#include "card/card.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void check_change_button_card();

void setup_kernel()
{
    DDRD &= ~(1 << PD2);  // entrada
    PORTD &= ~(1 << PD2); // pull-up DESLIGADO

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