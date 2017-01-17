#include "renderer.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_gfxPrimitives.h"

#include "window.h"


static bool draw_numbers(char ch, SDL_Rect *backrect, SDL_Rect *imgrect, SDL_Rect *dstrect);

static bool draw_small_letter(char ch, SDL_Rect *backrect, SDL_Rect *imgrect, SDL_Rect *dstrect);

static bool draw_big_letter(char ch, SDL_Rect *backrect, SDL_Rect *imgrect, SDL_Rect *dstrect);

static bool draw_special_symbol(char ch, SDL_Rect *backrect, SDL_Rect *imgrect, SDL_Rect *dstrect);


void draw_image_coord(SDL_Surface *surface, Point dst) 
{
	draw_image_coord_offset(surface, dst, (Point) { 0, 0 });
}

void draw_image_coord_offset(SDL_Surface *surface, Point dst, Point offset)
{
	SDL_Rect dstrect;

	dstrect.x = dst.x + offset.x;
	dstrect.y = dst.y + offset.y;

	SDL_BlitSurface(surface, NULL, get_screen(), &dstrect);
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

	SDL_Rect dstrect = { dst.x, dst.y };

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

static bool draw_numbers(char ch, SDL_Rect *backrect, SDL_Rect *imgrect, SDL_Rect *dstrect)
{
	if (('0' <= ch) && (ch <= '9'))
	{
		imgrect->x = 10 * (ch - '0');
		imgrect->y = 0;

		backrect->w = imgrect->w = 10;
		backrect->h = imgrect->h = 13;

		backrect->x = dstrect->x;

		SDL_BlitSurface(get_background_image(), backrect, get_screen(), dstrect);
		SDL_BlitSurface(get_symbols_image(), imgrect, get_screen(), dstrect);

		return true;
	}

	return false;
}

static bool draw_small_letter(char ch, SDL_Rect *backrect, SDL_Rect *imgrect, SDL_Rect *dstrect)
{
	if (('a' <= ch) && (ch <= 'z'))
	{
		imgrect->x = (ch - 'a') * 9;
		imgrect->y = 13;

		backrect->h = imgrect->h = 18;

		switch (ch)
		{
		case 'i':
		case 'l':
			backrect->w = imgrect->w = 4;

			break;
		case 'm':
			backrect->w = imgrect->w = 12;
			imgrect->x = ('l' - 'a') * 9 + 4;

			break;
		default:
			backrect->w = imgrect->w = 9;

			break;
		}

		backrect->x = dstrect->x;

		SDL_BlitSurface(get_background_image(), backrect, get_screen(), dstrect);
		SDL_BlitSurface(get_symbols_image(), imgrect, get_screen(), dstrect);

		return true;
	}

	return false;
}

static bool draw_big_letter(char ch, SDL_Rect *backrect, SDL_Rect *imgrect, SDL_Rect *dstrect)
{
	if (('A' <= ch) && (ch <= 'Z'))
	{
		imgrect->x = 11 * (ch - 'A');
		imgrect->y = 31;

		backrect->w = imgrect->w = 11;
		backrect->h = imgrect->h = 17;

		backrect->x = dstrect->x;

		SDL_BlitSurface(get_background_image(), backrect, get_screen(), dstrect);
		SDL_BlitSurface(get_symbols_image(), imgrect, get_screen(), dstrect);

		return true;
	}

	return false;
}

static bool draw_special_symbol(char ch, SDL_Rect *backrect, SDL_Rect *imgrect, SDL_Rect *dstrect)
{
	if (ch == ' ')
	{
		backrect->x = dstrect->x;
		backrect->h = 5;
		backrect->w = 5;

		SDL_BlitSurface(get_background_image(), backrect, get_screen(), dstrect);

		dstrect->x += 5;

		return true;
	}

	imgrect->w = 5;
	imgrect->h = 18;
	imgrect->y = 48;

	bool flag = false;

	switch (ch)
	{
	case ':':
		imgrect->x = 0;
		flag = true;

		break;
	case '.':
		imgrect->x = 10;
		flag = true;

		break;
	case ',':
		imgrect->x = 15;
		flag = true;

		break;
	case '!':
		imgrect->x = 5;
		flag = true;

		break;
	case '?':
		imgrect->x = 20;
		imgrect->w = 8;
		flag = true;

		break;
	}

	if (flag)
	{
		backrect->x = dstrect->x;
		backrect->w = imgrect->w;
		backrect->h = imgrect->h;

		SDL_BlitSurface(get_background_image(), backrect, get_screen(), dstrect);
		SDL_BlitSurface(get_symbols_image(), imgrect, get_screen(), dstrect);

		dstrect->x += imgrect->w;

		return true;
	}

	return false;
}

void draw_text_offset(char *text, Point dst, Point offset)
{
	dst.x += offset.x;
	dst.y += offset.y;

	SDL_Rect dstrect = { dst.x, dst.y };
	SDL_Rect backrect = { 0, dst.y, 0, 9 };
	SDL_Rect imgrect;

	int i = 0;

	while (text[i])
	{
		if (draw_numbers(text[i], &backrect, &imgrect, &dstrect))
		{
			dstrect.x += 10;
			++i;

			continue;
		}

		if (draw_small_letter(text[i], &backrect, &imgrect, &dstrect))
		{
			dstrect.x += backrect.w;
			++i;

			continue;
		}

		if (draw_big_letter(text[i], &backrect, &imgrect, &dstrect))
		{
			dstrect.x += 11;
			++i;

			continue;
		}

		draw_special_symbol(text[i], &backrect, &imgrect, &dstrect);

		++i;
	}
}

void draw_text(char *text, Point dst)
{
	draw_text_offset(text, dst, (Point) { 0, 0 });
}