.global delay_1ms

delay_1ms:
    ldi r17, 27      ; 1 ciclo
loop_externo:
    ldi r18, 200     ; 1 ciclo
loop_interno:
    dec r18          ; 1 ciclo
    brne loop_interno ; 2 ciclos
    dec r17          ; 1 ciclo
    brne loop_externo ; 2 ciclos
    ret              ; 4 ciclos (fora do cálculo)