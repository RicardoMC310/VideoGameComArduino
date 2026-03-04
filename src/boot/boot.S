.org 0x0000

_start:
    ldi r16, 0b00100000
    out 0x04, r16

_loop:
    cbi 0x05, 5

    rjmp _loop