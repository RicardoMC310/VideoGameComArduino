#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <avr/io.h>

typedef enum
{
    BTN_UP,
    BTN_DOWN,
    BTN_LEFT,
    BTN_RIGHT,
    BTN_A,
    BTN_B,
    BTN_NONE
} button_type_e;

int button_pressed(button_type_e btn);

#endif