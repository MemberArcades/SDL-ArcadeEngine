#pragma once

#include "SDL.h"

#include "block.h"
#include "imageloader.h"

#include <stdbool.h>


typedef struct
{
	int x;
	int y;
} Point;


void draw_image_coord(SDL_Surface *surface, Point dst);

void draw_image_coord_offset(SDL_Surface *surface, Point dst, Point offset);

void draw_background();

void draw_block_offset(enum BlockColor blockColor, Point dst, Point offset);

void draw_block(enum BlockColor blockColor, Point dst);

void draw_text_offset(char *text, Point dst, Point offset);

void draw_text(char *text, Point dst);