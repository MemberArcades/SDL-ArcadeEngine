#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "block.h"

SDL_Surface *load_image(char *filename);

void load_images();

void destroy_image();

SDL_Surface* get_block_image(BlockImage block);

SDL_Surface* get_background_image();

SDL_Surface* get_game_over_image();