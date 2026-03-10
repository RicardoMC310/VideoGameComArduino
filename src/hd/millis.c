#include "hd/millis.h"
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint32_t timer1_millis = 0;

ISR(TIMER1_COMPA_vect) {
    timer1_millis++;
}

uint32_t millis1(void)
{
    uint32_t m;
    uint8_t sreg = SREG;

    cli();
    m = timer1_millis;
    SREG = sreg;

    return m;
}