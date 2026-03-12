#include "hd/sound.h"
#include "hd/millis.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

static volatile uint32_t tone_end = 0;
static volatile uint8_t playing = 0;

static volatile const note_t *melody = 0;
static volatile uint16_t melody_length = 0;
static volatile uint16_t melody_index = 0;
static volatile uint8_t melody_playing = 0;

static volatile uint16_t bpm = 120;
static volatile uint32_t beat_ms = 500;

static volatile uint8_t note_finished = 0;

ISR(TIMER2_COMPA_vect)
{
    PORTB ^= (1 << PB3);
}

void sound_init()
{
    DDRB |= (1 << PB3);
    PORTB &= ~(1 << PB3);

    TCCR2A = (1 << WGM21); // CTC
    TCCR2B = 0;

    TIMSK2 = 0;
}

void sound_play_tone(uint16_t freq, uint16_t duration)
{
    if (playing)
        return;

    uint32_t ocr;
    uint8_t prescaler_bits;
    uint8_t prescaler_value = 0;

    // Array com os prescalers disponíveis no Timer2
    const uint8_t prescalers[] = {8, 32, 64, 128, 256, 1024};
    const uint8_t prescaler_configs[] = {
        (1 << CS21),                            // 8
        (1 << CS21) | (1 << CS20),              // 32
        (1 << CS22),                            // 64
        (1 << CS22) | (1 << CS20),              // 128
        (1 << CS22) | (1 << CS21),              // 256
        (1 << CS22) | (1 << CS21) | (1 << CS20) // 1024
    };

    // Tenta encontrar o melhor prescaler
    for (int i = 0; i < 6; i++)
    {
        ocr = (F_CPU / (2UL * prescalers[i] * freq)) - 1;

        if (ocr <= 255 && ocr > 0)
        {
            prescaler_value = prescalers[i];
            prescaler_bits = prescaler_configs[i];
            break;
        }
    }

    // Se não encontrou um prescaler adequado
    if (prescaler_value == 0)
    {
        // Usa o maior prescaler (1024) e ajusta
        ocr = (F_CPU / (2UL * 1024 * freq)) - 1;
        if (ocr > 255)
            ocr = 255;
        if (ocr < 1)
            ocr = 1;
        prescaler_bits = (1 << CS22) | (1 << CS21) | (1 << CS20); // 1024
    }

    cli();

    TCCR2B = prescaler_bits;
    TCNT2 = 0;
    OCR2A = (uint8_t)ocr;

    tone_end = millis1() + duration;
    playing = 1;
    note_finished = 0;

    TIMSK2 |= (1 << OCIE2A);

    sei();
}

void sound_stop_tone()
{
    cli();
    TIMSK2 &= ~(1 << OCIE2A); // desliga interrupção
    PORTB &= ~(1 << PB3);
    playing = 0;
    note_finished = 1; // Indica que a nota terminou
    sei();
}

static uint16_t sound_note_duration(uint16_t length)
{
    return (beat_ms * 4) / length;
};

void sound_update()
{
    uint32_t now = millis1();

    // Verifica se a nota atual terminou
    if (playing && now >= tone_end)
    {
        sound_stop_tone();
    }

    // Se não está tocando melodia, sai
    if (!melody_playing)
        return;

    // Se está tocando uma nota OU esperando uma pausa, aguarda
    if (playing)
        return;
        
    // Verifica se está no meio de uma pausa
    if (now < tone_end)
        return;

    // Se chegou ao fim da melodia
    if (melody_index >= melody_length)
    {
        melody_playing = 0;
        sound_stop_tone();
        return;
    }

    // Toca a próxima nota
    note_t n;
    n.note = pgm_read_word(&melody[melody_index].note);
    n.duration = pgm_read_word(&melody[melody_index].duration);

    uint16_t duration = sound_note_duration(n.duration);

    if (n.note == NOTE_REST)
    {
        // CORREÇÃO: Não para o som (já deve estar parado)
        // Apenas configura o tempo da pausa
        tone_end = now + duration;
        melody_index++;
        // IMPORTANTE: playing continua 0, mas tone_end indica quando a pausa acaba
    }
    else
    {
        sound_play_tone(n.note, duration);
        melody_index++;
    }
}

int sound_playing()
{
    return (playing || melody_playing);
}

void sound_play_melody(const note_t *m, uint16_t len)
{
    // Para qualquer melodia anterior
    sound_stop_melody();

    melody = m;
    melody_length = len;
    melody_index = 0;
    melody_playing = 1;
    note_finished = 0;
}

void sound_stop_melody()
{
    melody_playing = 0;
    sound_stop_tone();
}

void sound_set_bpm(uint16_t new_bpm)
{
    bpm = new_bpm;
    beat_ms = 60000UL / bpm;
}