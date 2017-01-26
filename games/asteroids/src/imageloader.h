#pragma once

#include <SDL.h>
#include <SDL_image.h>

#define DIR_IMAGE "image/"


SDL_Surface *load_image(char *filename);

void load_images();

void destroy_image();

SDL_Surface* get_logo_image();

SDL_Surface* get_instruction_image();