#include "hd/millis.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void setup_kernel() {
    DDRB |= (1 << PB5);
    PORTB &= ~(1 << PB5);
}

void loop_kernel() {
    static uint32_t lastTime = 0;
    uint32_t currentTime = millis1();
    
    if (currentTime - lastTime >= 1000) {
        lastTime = currentTime;
        PORTB ^= (1 << PB5);
    }
}