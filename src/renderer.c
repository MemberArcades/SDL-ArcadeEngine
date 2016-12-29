#include "renderer.h"

#include "SDL.h"
#include "SDL_image.h"

#include <math.h>

#include "window.h"

void draw_image_coord(SDL_Surface *surface, Point dst) 
{
	Point nulOffset;
	nulOffset.x = 0;
	nulOffset.y = 0;

	draw_image_coord_offset(surface, dst, nulOffset);
}

void draw_image_coord_offset(SDL_Surface *surface, Point dst, Point offset)
{
	SDL_Rect dstrect;

	dstrect.x = (int)dst.x + (int)offset.x;
	dstrect.y = (int)dst.y + (int)offset.y;

	SDL_BlitSurface(surface, NULL, get_screen(), &dstrect);
}

void draw_point(SDL_Surface *surface, Point dst, Uint32 color)
{
	SDL_Rect fillRect = { dst.x, dst.y, 1, 1 };
	SDL_FillRect(surface, &fillRect, color);
}

void draw_line(SDL_Surface *surface, Point begin, Point end, Uint32 color) 
{
	Point point;
	point.x = end.x - begin.x;
	point.y = end.y - begin.y;
	double length = sqrt(point.x * point.x + point.y * point.y);

	Point add;
	add.x = point.x / length;
	add.y = point.y / length;

	point.x = begin.x;
	point.y = begin.y;

	for (int i = 0; i < length; i += 1) 
	{
		draw_point(surface, point, color);
		point.x += add.x;
		point.y += add.y;
	}
}
