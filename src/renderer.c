#include "renderer.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_gfxPrimitives.h"

#include <math.h>

#include "window.h"
#include "player.h"

void draw_image_coord(SDL_Surface *surface, Vector dst) 
{
	Vector nulOffset;
	nulOffset.x = 0;
	nulOffset.y = 0;

	draw_image_coord_offset(surface, dst, nulOffset);
}

void draw_image_coord_offset(SDL_Surface *surface, Vector dst, Vector offset)
{
	SDL_Rect dstrect;

	dstrect.x = dst.x + offset.x;
	dstrect.y = dst.y + offset.y;

	SDL_BlitSurface(surface, NULL, get_screen(), &dstrect);
}

void draw_point(SDL_Surface *surface, Vector dst, Uint32 color)
{
	/* color format: 0xRRGGBBAA */
	pixelColor(surface, dst.x, dst.y, color);
}

void draw_line(SDL_Surface *surface, Vector begin, Vector end, Uint32 color) 
{
	/* color format: 0xRRGGBBAA */
	lineColor(surface, begin.x, begin.y, end.x, end.y, color);
}

void draw_physics_body(SDL_Surface *surface, PhysicsBody body)
{
	int total = body.collider.points_count;
	Vector pos = body.position;

	Vector first_point = sum_vector(pos, body.collider.points[0]);
	Vector last_point = sum_vector(pos, body.collider.points[total - 1]);

	for (size_t i = 1; i < total; ++i)
	{
		draw_line
		(
			surface,
			sum_vector(pos, body.collider.points[i - 1]),
			sum_vector(pos, body.collider.points[i]),
			0xFFFFFFFF
		);
	}

	draw_line(surface, first_point, last_point, 0xFFFFFFFF);
}

void draw_player(SDL_Surface *surface, Player player)
{
	draw_physics_body(surface, player.body);
}

void draw_enemy(SDL_Surface *surface, Enemy enemy)
{
	if (enemy.alive)
		draw_physics_body(surface, enemy.body);
}