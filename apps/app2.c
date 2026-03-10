#include "card/card.h"
#include "hd/millis.h"
#include "hd/delay.h"
#include "hd/button.h"

#include <avr/io.h>

static volatile uint32_t last_time;
static volatile uint32_t timer;

static void app_setup()
{
    DDRB |= (1 << PB4); // LED como saída
    PORTB &= ~(1 << PB4);
    last_time = 0;
    timer = 350;
}

static void app_update()
{
    if (button_pressed(BTN_UP))
        timer = 700;
    if (button_pressed(BTN_DOWN))
        timer = 800;
    if (button_pressed(BTN_LEFT))
        timer = 900;
    if (button_pressed(BTN_RIGHT))
        timer = 1000;
    if (button_pressed(BTN_A))
        timer = 1500;
    if (button_pressed(BTN_B))
        timer = 2000;

    uint32_t now = millis1();

    if (now - last_time >= timer)
    {
        PORTB ^= (1 << PB4);
        last_time = now;
    }
}

static void app_exit()
{
    PORTB &= ~(1 << PB4);
    DDRB &= ~(1 << PB4); // LED como entrada
}

app_vtable_t app2_vtable = {
    .func_setup = app_setup,
    .func_update = app_update,
    .func_exit = app_exit,
};