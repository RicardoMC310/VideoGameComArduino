#ifndef __SOUND_H__
#define __SOUND_H__

#include "sound/note.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void sound_init();
void sound_play_tone(uint16_t freq, uint16_t duration);
void sound_stop_tone();
void sound_update();
int sound_playing();
void sound_play_melody(const note_t *m, uint16_t len);
void sound_stop_melody();
void sound_set_bpm(uint16_t new_bpm);

#endif