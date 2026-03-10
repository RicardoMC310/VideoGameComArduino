#include "card/card.h"
#include "hd/millis.h"
#include "hd/delay.h"
#include "hd/button.h"

#include <avr/io.h>

static void app_setup()
{
    DDRB |= (1 << PB4); // LED como saída
}

static void app_update()
{
    if (button_pressed(BTN_UP))
    {
        PORTB ^= (1 << PB4);
        delay(100);
    }

    if (button_pressed(BTN_DOWN))
    {
        PORTB ^= (1 << PB4);
        delay(200);
    }

    if (button_pressed(BTN_LEFT))
    {
        PORTB ^= (1 << PB4);
        delay(300);
    }

    if (button_pressed(BTN_RIGHT))
    {
        PORTB ^= (1 << PB4);
        delay(400);
    }

    if (button_pressed(BTN_A))
    {
        PORTB ^= (1 << PB4);
        delay(500);
    }

    if (button_pressed(BTN_B))
    {
        PORTB ^= (1 << PB4);
        delay(600);
    }
}

static void app_exit()
{
    PORTB &= ~(1 << PB4);
    DDRB &= ~(1 << PB4); // LED como entrada
}

app_vtable_t app1_vtable = {
    .func_setup = app_setup,
    .func_update = app_update,
    .func_exit = app_exit,
};