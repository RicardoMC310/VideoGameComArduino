#include "hd/delay.h"

void delay(uint16_t ms)
{
    for(uint16_t i = 0; i < ms; i++)
    {
        delay_1ms();
    }
}