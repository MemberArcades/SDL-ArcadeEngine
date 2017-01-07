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

	SDL_Rect dstrect = { (int)dst.x, (int)dst.y };

	SDL_Rect imgrect = { 0, 0, 32, 32 };

	switch (blockColor)
	{
	case BackgroundColor:
		imgrect.x = X_MAIN_FIELD;
		imgrect.y = Y_MAIN_FIELD;

		SDL_BlitSurface(get_background_image(), &imgrect, get_screen(), &dstrect);

		break;
	case RedColor:
		imgrect.x = 32;

		SDL_BlitSurface(get_block_image(), &imgrect, get_screen(), &dstrect);

		break;
	case BlueColor:
		imgrect.x = 32;
		imgrect.y = 32;

		SDL_BlitSurface(get_block_image(), &imgrect, get_screen(), &dstrect);

		break;
	case GreenColor:
		SDL_BlitSurface(get_block_image(), &imgrect, get_screen(), &dstrect);

		break;
	case PurpleColor:
		imgrect.y = 32;

		SDL_BlitSurface(get_block_image(), &imgrect, get_screen(), &dstrect);
		break;
	}

}

void draw_block(BlockColor blockColor, Point dst)
{
	draw_block_offset(blockColor, dst, (Point) { 0, 0 });
}

void draw_text_offset(char *text, Point dst, Point offset)
{
	dst.x += offset.x;
	dst.y += offset.y;

	SDL_Rect dstrect = { (int)dst.x, (int)dst.y };
	SDL_Rect backrect = { 0, (int)dst.y, 0, 9 };
	SDL_Rect imgrect;

	int i = 0;

	while (text[i])
	{
		if (('0' <= text[i]) && (text[i] <= '9'))
		{
			imgrect.x = 10 * (text[i] - '0');
			imgrect.y = 0;

			backrect.w = imgrect.w = 10;
			backrect.h = imgrect.h = 13;

			backrect.x = dstrect.x;

			SDL_BlitSurface(get_background_image(), &backrect, get_screen(), &dstrect);
			SDL_BlitSurface(get_symbols_image(), &imgrect, get_screen(), &dstrect);

			dstrect.x += 10;
			++i;

			continue;
		}

		if (('a' <= text[i]) && (text[i] <= 'z'))
		{
			imgrect.x = (text[i] - 'a') * 9;
			imgrect.y = 13;

			backrect.h = imgrect.h = 18;

			int index = 0;

			switch (text[i])
			{
			case 'i':
			case 'l':
				backrect.w = index = imgrect.w = 4;
				break;
			case 'm':
				backrect.w = index = imgrect.w = 12;
				imgrect.x = ('l' - 'a') * 9 + 4;
				break;
			default:
				backrect.w = index = imgrect.w = 9;
				break;
			}

			backrect.x = dstrect.x;

			SDL_BlitSurface(get_background_image(), &backrect, get_screen(), &dstrect);
			SDL_BlitSurface(get_symbols_image(), &imgrect, get_screen(), &dstrect);

			dstrect.x += index;
			++i;

			continue;
		}

		if (('A' <= text[i]) && (text[i] <= 'Z'))
		{
			imgrect.x = 11 * (text[i] - 'A');
			imgrect.y = 31;

			backrect.w = imgrect.w = 11;
			backrect.h = imgrect.h = 17;

			backrect.x = dstrect.x;

			SDL_BlitSurface(get_background_image(), &backrect, get_screen(), &dstrect);
			SDL_BlitSurface(get_symbols_image(), &imgrect, get_screen(), &dstrect);

			dstrect.x += 11;
			++i;

			continue;
		}

		if (text[i] == ' ')
		{
			backrect.x = dstrect.x;
			backrect.h = 5;
			backrect.w = 5;

			SDL_BlitSurface(get_background_image(), &backrect, get_screen(), &dstrect);

			dstrect.x += 5;
			++i;

			continue;
		}

		imgrect.w = 5;
		imgrect.h = 18;
		imgrect.y = 48;

		bool flag = false;

		switch (text[i])
		{
		case ':':
			imgrect.x = 0;
			flag = true;

			break;
		case '.':
			imgrect.x = 10;
			flag = true;

			break;
		case ',':
			imgrect.x = 15;
			flag = true;

			break;
		case '!':
			imgrect.x = 5;
			flag = true;

			break;
		case '?':
			imgrect.x = 20;
			imgrect.w = 8;
			flag = true;

			break;
		}

		if (flag)
		{
			backrect.x = dstrect.x;
			backrect.w = imgrect.w;
			backrect.h = imgrect.h;

			SDL_BlitSurface(get_background_image(), &backrect, get_screen(), &dstrect);
			SDL_BlitSurface(get_symbols_image(), &imgrect, get_screen(), &dstrect);

			dstrect.x += imgrect.w;
		}

		++i;
	}
}

void draw_text(char *text, Point dst)
{
	draw_text_offset(text, dst, (Point) { 0, 0 });
}