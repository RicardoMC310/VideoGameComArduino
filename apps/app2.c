#include "card/card.h"
#include "hd/millis.h"
#include "hd/delay.h"
#include "hd/button.h"
#include "hd/sound.h"
#include "sound/note.h"

#include <avr/io.h>
#include <avr/pgmspace.h>

const note_t spongebob[] PROGMEM = {
    {NOTE_REST, 4},

    // =========================================
    // INTRODUÇÃO - O riff característico
    // =========================================
    {NOTE_REST, 8},
    {NOTE_C5, 8},
    {NOTE_REST, 8},
    {NOTE_C5, 8},
    {NOTE_REST, 8},
    {NOTE_C5, 8},
    {NOTE_REST, 8},
    {NOTE_C5, 8},
    {NOTE_REST, 8},

    // =========================================
    // TEMA PRINCIPAL (loop que fica na cabeça)
    // =========================================
    // Frase 1
    {NOTE_C5, 4},
    {NOTE_AS4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},
    {NOTE_C5, 4},
    {NOTE_AS4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},

    // Frase 2
    {NOTE_DS5, 4},
    {NOTE_D5, 8},
    {NOTE_C5, 8},
    {NOTE_AS4, 8},
    {NOTE_C5, 8},
    {NOTE_DS5, 4},
    {NOTE_D5, 8},
    {NOTE_C5, 8},
    {NOTE_AS4, 8},
    {NOTE_C5, 8},

    // =========================================
    // SEGUNDA PARTE (variação)
    // =========================================
    {NOTE_F5, 4},
    {NOTE_DS5, 8},
    {NOTE_D5, 8},
    {NOTE_C5, 8},
    {NOTE_AS4, 8},
    {NOTE_G5, 4},
    {NOTE_F5, 8},
    {NOTE_DS5, 8},
    {NOTE_D5, 8},
    {NOTE_C5, 8},

    {NOTE_C5, 4},
    {NOTE_AS4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},
    {NOTE_C5, 2},
    {NOTE_REST, 4},

    // =========================================
    // RETORNO AO TEMA
    // =========================================
    {NOTE_C5, 4},
    {NOTE_AS4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},
    {NOTE_C5, 4},
    {NOTE_AS4, 8},
    {NOTE_G4, 8},
    {NOTE_F4, 8},
    {NOTE_G4, 8},

    {NOTE_DS5, 4},
    {NOTE_D5, 8},
    {NOTE_C5, 8},
    {NOTE_AS4, 8},
    {NOTE_C5, 8},
    {NOTE_DS5, 4},
    {NOTE_D5, 8},
    {NOTE_C5, 8},
    {NOTE_AS4, 8},
    {NOTE_C5, 8},

    // =========================================
    // FINAL
    // =========================================
    {NOTE_F5, 4},
    {NOTE_DS5, 8},
    {NOTE_D5, 8},
    {NOTE_C5, 8},
    {NOTE_AS4, 8},
    {NOTE_G5, 2},
    {NOTE_REST, 2},

    {NOTE_C5, 1} // Nota final longa
    // Pausa final
};

static void app_setup()
{
    DDRB |= (1 << PB4); // LED como saída
    PORTB &= ~(1 << PB4);
    sound_set_bpm(135);
}

static void app_update()
{
    if (!sound_playing())
        sound_play_melody(spongebob, sizeof(spongebob) / sizeof(spongebob[0]));
}

static void app_exit()
{
    PORTB &= ~(1 << PB4);
    DDRB &= ~(1 << PB4); // LED como entrada
    sound_stop_melody();
}

app_vtable_t app2_vtable = {
    .func_setup = app_setup,
    .func_update = app_update,
    .func_exit = app_exit,
};