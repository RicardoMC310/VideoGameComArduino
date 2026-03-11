#include "card/card.h"
#include "hd/millis.h"
#include "hd/delay.h"
#include "hd/button.h"
#include "hd/sound.h"
#include "sound/note.h"

#include <avr/io.h>
#include <avr/pgmspace.h>

const note_t mario[] PROGMEM = {
    {NOTE_REST, 4},
    // Parte 1 - Introdução (clássica do Mario)
    {NOTE_E5, 8},
    {NOTE_E5, 8},
    {NOTE_REST, 8},
    {NOTE_E5, 8},
    {NOTE_REST, 8},
    {NOTE_C5, 8},
    {NOTE_E5, 8},
    {NOTE_G5, 8},
    {NOTE_REST, 4},
    {NOTE_G4, 4},
    {NOTE_REST, 4},

    // Parte 2 - Descida (mais conectada)
    {NOTE_C5, 4},
    {NOTE_REST, 8},
    {NOTE_G4, 4},
    {NOTE_REST, 8},
    {NOTE_E4, 4},
    {NOTE_REST, 8},
    {NOTE_A4, 4},
    {NOTE_REST, 8},
    {NOTE_B4, 4},
    {NOTE_REST, 8},
    {NOTE_AS4, 8},
    {NOTE_A4, 8},
    {NOTE_G4, 4},
    {NOTE_E5, 8},
    {NOTE_G5, 8},
    {NOTE_A5, 4},
    {NOTE_F5, 8},
    {NOTE_G5, 8},
    {NOTE_REST, 8},
    {NOTE_E5, 8},
    {NOTE_C5, 8},
    {NOTE_D5, 8},
    {NOTE_B4, 4},
    {NOTE_REST, 2},

    // Parte 3 - Refrão principal
    {NOTE_C5, 4},
    {NOTE_REST, 8},
    {NOTE_G4, 4},
    {NOTE_REST, 8},
    {NOTE_E4, 4},
    {NOTE_REST, 8},
    {NOTE_A4, 4},
    {NOTE_REST, 8},
    {NOTE_B4, 4},
    {NOTE_REST, 8},
    {NOTE_AS4, 8},
    {NOTE_A4, 8},
    {NOTE_G4, 4},
    {NOTE_E5, 8},
    {NOTE_G5, 8},
    {NOTE_A5, 4},
    {NOTE_F5, 8},
    {NOTE_G5, 8},
    {NOTE_REST, 8},
    {NOTE_E5, 8},
    {NOTE_C5, 8},
    {NOTE_D5, 8},
    {NOTE_B4, 4},
    {NOTE_REST, 2},

    // Ponte (mantém o ritmo)
    {NOTE_G5, 8},
    {NOTE_FS5, 8},
    {NOTE_F5, 8},
    {NOTE_DS5, 8},
    {NOTE_E5, 4},
    {NOTE_REST, 8},
    {NOTE_GS4, 8},
    {NOTE_A4, 8},
    {NOTE_C5, 4},
    {NOTE_REST, 8},
    {NOTE_A4, 8},
    {NOTE_C5, 8},
    {NOTE_D5, 4},
    {NOTE_REST, 8},
    {NOTE_G5, 8},
    {NOTE_FS5, 8},
    {NOTE_F5, 8},
    {NOTE_DS5, 8},
    {NOTE_E5, 4},
    {NOTE_REST, 8},
    {NOTE_C6, 4},
    {NOTE_C6, 4},
    {NOTE_C6, 4},
    {NOTE_REST, 2},

    // Repetição do refrão
    {NOTE_C5, 4},
    {NOTE_REST, 8},
    {NOTE_G4, 4},
    {NOTE_REST, 8},
    {NOTE_E4, 4},
    {NOTE_REST, 8},
    {NOTE_A4, 4},
    {NOTE_REST, 8},
    {NOTE_B4, 4},
    {NOTE_REST, 8},
    {NOTE_AS4, 8},
    {NOTE_A4, 8},
    {NOTE_G4, 4},
    {NOTE_E5, 8},
    {NOTE_G5, 8},
    {NOTE_A5, 4},
    {NOTE_F5, 8},
    {NOTE_G5, 8},
    {NOTE_REST, 8},
    {NOTE_E5, 8},
    {NOTE_C5, 8},
    {NOTE_D5, 8},
    {NOTE_B4, 4},
    {NOTE_REST, 2},

    // Final (dramático mas sem exageros)
    {NOTE_E5, 2},
    {NOTE_C5, 2},
    {NOTE_G4, 2},
    {NOTE_REST, 2}}; // Pausa final longa

static void app_setup()
{
    DDRB |= (1 << PB4); // LED como saída
    PORTB &= ~(1 << PB4);
    sound_set_bpm(170);
}

static void app_update()
{
    if (!sound_playing())
        sound_play_melody(mario, sizeof(mario) / sizeof(mario[0]));
}

static void app_exit()
{
    PORTB &= ~(1 << PB4);
    DDRB &= ~(1 << PB4); // LED como entrada
    sound_stop_melody();
}

app_vtable_t app1_vtable = {
    .func_setup = app_setup,
    .func_update = app_update,
    .func_exit = app_exit,
};