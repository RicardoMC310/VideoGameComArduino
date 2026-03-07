#include "card/card.h"
#include "hd/millis.h"

#include <avr/io.h>

static uint32_t last_time = 0;

static void app_setup()
{
    DDRB |= (1 << PB4); // LED como saída
    last_time = 0;
}

static void app_update()
{
    uint32_t current_time = millis1();

    if (current_time - last_time >= 1000)
    {
        PORTB ^= (1 << PB4);
        last_time = current_time;
    }
}

static void app_exit()
{
    DDRB &= ~(1 << PB4); // LED como entrada
}

app_vtable_t app1_vtable = {
    .func_setup = app_setup,
    .func_update = app_update,
    .func_exit = app_exit,
};