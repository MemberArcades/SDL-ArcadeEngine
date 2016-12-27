#pragma once

#include <stdbool.h>
#include "SDL.h"

void draw_point(SDL_Surface *surface, int x, int y, Uint32 color);

void draw_line(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 color);
