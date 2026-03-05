.section .text
.global main
.extern setup_kernel
.extern loop_kernel

main:
    ; Inicializar stack pointer (RAMEND = 0x08FF para ATMega328P)
    ldi r16, 0xFF
    out 0x3D, r16    ; SPL
    ldi r16, 0x08
    out 0x3E, r16    ; SPH

    ; Configurar Timer1 para 1ms
    ; Para endereços > 0x3F, usamos STS (Store to SRAM)
    
    ; TCCR1A = 0 (endereço 0x80)
    ldi r16, 0
    sts 0x80, r16    ; TCCR1A

    ; TCCR1B = (1 << WGM12) - CTC mode (endereço 0x81)
    ldi r16, (1 << 3)  ; WGM12 é bit 3
    sts 0x81, r16    ; TCCR1B

    ; OCR1A = 249 (endereços 0x88 e 0x89)
    ldi r16, 0xF9     ; 249 em hex
    sts 0x88, r16    ; OCR1AL
    ldi r16, 0
    sts 0x89, r16    ; OCR1AH

    ; TCNT1 = 0 (endereços 0x84 e 0x85)
    ldi r16, 0
    sts 0x84, r16    ; TCNT1L
    sts 0x85, r16    ; TCNT1H

    ; TIMSK1 = (1 << OCIE1A) (endereço 0x6F)
    ldi r16, (1 << 1)  ; OCIE1A é bit 1
    sts 0x6F, r16    ; TIMSK1

    ; Iniciar timer com prescaler 64
    ; Para ler/modificar registros > 0x3F, usamos LDS/STS
    lds r16, 0x81     ; lê TCCR1B atual
    ori r16, (1 << 1) | (1 << 0)  ; CS11 e CS10 são bits 1 e 0
    sts 0x81, r16    ; escreve TCCR1B

    ; Habilitar interrupções globais
    sei

    call setup_kernel

loop:
    call loop_kernel
    rjmp loop