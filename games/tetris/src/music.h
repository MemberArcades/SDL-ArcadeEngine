#pragma once

#include <SDL.h>
#include "SDL_mixer.h"


#define DIR_SOUND "sound/"

#define VOLUME_STEP 5
#define VOLUME_START 5


void load_sound();

void sound_key(int key);

void sound_volum_minus();

void sound_volum_plus();

void sound();

void sound_pause();

void destroy_sound();