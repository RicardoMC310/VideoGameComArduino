#include "hd/delay.h"

#include <stdint.h>

void setup_kernel()
{
    (*(volatile uint8_t *)0x24) |= (1 << 5);
}

void loop_kernel()
{
    (*(volatile uint8_t *)0x25) |= (1 << 5);

    delay(500);

    (*(volatile uint8_t *)0x25) &= ~(1 << 5);

    delay(100);
}