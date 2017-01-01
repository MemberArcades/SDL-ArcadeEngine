#pragma once

#include <stdbool.h>
#include "SDL.h"

#include "imageloader.h"

typedef struct
{
	double x;
	double y;
} Point;

void draw_image_coord(SDL_Surface *surface, Point dst);

void draw_image_coord_offset(SDL_Surface *surface, Point dst, Point offset);

void draw_point(SDL_Surface *surface, Point dst, Uint32 color);

void draw_line(SDL_Surface *surface, Point begin, Point end, Uint32 color);

void draw_background();

void draw_block_offset(BlockColor blockColor, Point dst, Point offset);

void draw_block(BlockColor blockColor, Point dst);