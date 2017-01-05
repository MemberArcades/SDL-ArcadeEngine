#pragma once

#include "SDL_mixer.h"
#include <SDL.h>


#define DIR_SOUND "sound/"

#define VOLUME_STEP 5
#define VOLUME_START 5


void load_sound();


void sound_key(int key);