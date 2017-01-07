#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "block.h"


#define DIR_IMAGE "image/"

#define NUMBER_OF_SKINS 2


void load_images();

void destroy_image();

SDL_Surface* get_block_image();

SDL_Surface* get_background_image();

SDL_Surface* get_game_over_image();

SDL_Surface* get_symbols_image();