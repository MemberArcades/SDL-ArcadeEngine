#include "renderer.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_gfxPrimitives.h"

#include <math.h>

#include "window.h"

void draw_image_coord(SDL_Surface *surface, Point dst) 
{
	draw_image_coord_offset(surface, dst, (Point) { 0, 0 });
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
	SDL_Rect fillRect = { (int)dst.x, (int)dst.y, 1, 1 };
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

void draw_background()
{
	clear_screen(0x00, 0x00, 0x00, 0xFF);
	draw_image_coord(get_background_image(), (Point) { 0, 0 });
}

void draw_block_offset(BlockColor blockColor, Point dst, Point offset)
{
	dst.x += offset.x;
	dst.y += offset.y;

	if (blockColor == BackgroundColor)
	{
		draw_image_coord(get_block_image(BackgroundImage), dst);
	}
	else
	{
		SDL_Rect dstrect = { (int)dst.x, (int)dst.y };

		SDL_Rect imgrect = { 0, 0, 32, 32 };

		switch (blockColor)
		{
		case RedColor:
			imgrect.x = 32;

			SDL_BlitSurface(get_block_image(OtherImage), &imgrect, get_screen(), &dstrect);

			break;
		case BlueColor:
			imgrect.x = 32;
			imgrect.y = 32;

			SDL_BlitSurface(get_block_image(OtherImage), &imgrect, get_screen(), &dstrect);

			break;
		case GreenColor:
			SDL_BlitSurface(get_block_image(OtherImage), &imgrect, get_screen(), &dstrect);

			break;
		case PurpleColor:
			imgrect.y = 32;

			SDL_BlitSurface(get_block_image(OtherImage), &imgrect, get_screen(), &dstrect);
			break;
		}
	}
}

void draw_block(BlockColor blockColor, Point dst)
{
	draw_block_offset(blockColor, dst, (Point) { 0, 0 });
}