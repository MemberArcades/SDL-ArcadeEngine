#include "renderer.h"

#include "SDL.h"
#include "SDL_image.h"

#include <math.h>

#include "window.h"

/* выводит изображение по заданым координатам */
void draw_image_coord(SDL_Surface *surface, int x, int y);
void draw_image_coord_offset(SDL_Surface *surface, int x, int y, int xOffset, int yOffset);

void draw_image_coord(SDL_Surface *surface, int x, int y)
{
	draw_image_coord_offset(surface, x, y, 0, 0);
}

void draw_image_coord_offset(SDL_Surface *surface, int x, int y, int xOffset, int yOffset)
{
	int pixPerTile = 16;
	apply_surface(pixPerTile * x + xOffset, pixPerTile * y + yOffset, surface);
}

void draw_point(SDL_Surface *surface, int x, int y, Uint32 color)
{
	SDL_Rect fillRect = { x, y, 1, 1 };
	SDL_FillRect(surface, &fillRect, color);
}

void draw_line(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 color) {

	double x = x1 - x0;
	double y = y1 - y0;
	double length = sqrt(x * x + y * y);
	double addx = x / length;
	double addy = y / length;

	x = x0;
	y = y0;

	for (int i = 0; i < length; i += 1) 
	{
		draw_point(surface, x, y, color);
		x += addx;
		y += addy;
	}
}
