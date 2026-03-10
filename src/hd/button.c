#include "hd/button.h"

#include <avr/io.h>
#include <stdint.h>
#include <stddef.h>

struct button_map_t {
    button_type_e type;
    volatile uint8_t *pin;
    uint8_t bit;
};

static struct button_map_t buttons_map[] = {
    {BTN_UP, &PIND, 3},
    {BTN_LEFT, &PIND, 4},
    {BTN_RIGHT, &PIND, 5},
    {BTN_DOWN, &PIND, 6},
    {BTN_A, &PIND, 7},
    {BTN_B, &PINB, 0},
    {BTN_NONE, NULL, 0}
};

int button_pressed(button_type_e btn)
{
    for (int i = 0; buttons_map[i].type != BTN_NONE; i++)
    {
        if (buttons_map[i].type == btn)
        {
            return (*(buttons_map[i].pin) & (1 << buttons_map[i].bit)) != 0;
        }
    }
}