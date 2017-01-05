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

	if (player.thrust)
	{
		PhysicsBody exhaust = (PhysicsBody) { 
			.collider.points_count = 3,
			.collider.points = { (Vector) { 0, -7 }, (Vector) { -3, 0 }, (Vector) { 3, 0 } },
			.position = player.body.position		
		};

		for (int i = 0; i < 3; ++i)
			rotate_vector(&exhaust.collider.points[i], player.angle);

		draw_physics_body(surface, exhaust);
	}

	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		draw_bullet(get_screen(), player.bullets[i]);
	}
}

void draw_enemy(SDL_Surface *surface, Enemy enemy)
{
	if (enemy.alive)
		draw_physics_body(surface, enemy.body);
}

void draw_bullet(SDL_Surface *surface, Bullet bullet)
{
	if (bullet.alive)
		draw_physics_body(surface, bullet.body);
}