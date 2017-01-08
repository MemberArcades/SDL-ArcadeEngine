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

	for (int i = 1; i < total; ++i)
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

void draw_hud(SDL_Surface *surface, Player player)
{
	int x_offset = 25;
	int y_offset = 35;
	int period = 15;

	for (int i = 0; i < player.lives; ++i)
	{
		draw_line(surface, (Vector) { x_offset + 0, y_offset + -15 }, (Vector) { x_offset + -5, y_offset + 0 }, 0xFFFFFFFF);
		draw_line(surface, (Vector) { x_offset + 0, y_offset + -15 }, (Vector) { x_offset + 5, y_offset + 0 }, 0xFFFFFFFF);
		draw_line(surface, (Vector) { x_offset + 5, y_offset + 0 }, (Vector) { x_offset + -5, y_offset + 0 }, 0xFFFFFFFF);

		x_offset += period;
	}
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
		draw_bullet(surface, player.bullets[i]);
	}
}

void draw_player_crash(SDL_Surface *surface, Player player)
{
	unsigned cur_time = SDL_GetTicks();
	unsigned delta = 1 + (cur_time - player.crash_time) * 0.01;

	PhysicsBody first_fragment;
	first_fragment.collider.points_count = 2;
	first_fragment.collider.points[0] = player.body.collider.points[0];
	first_fragment.collider.points[1] = player.body.collider.points[1];
	first_fragment.position = player.body.position;
		
	Vector first_fragment_dir = player.body.collider.points[0];
	normalise_vector(&first_fragment_dir);
	mul_vector(&first_fragment_dir, delta);
	add_vector(&first_fragment.position, first_fragment_dir);

	PhysicsBody second_fragment;
	second_fragment.collider.points_count = 2;
	second_fragment.collider.points[0] = player.body.collider.points[1];
	second_fragment.collider.points[1] = player.body.collider.points[2];
	second_fragment.position = player.body.position;

	Vector second_fragment_dir = player.body.collider.points[1];
	normalise_vector(&second_fragment_dir);
	mul_vector(&second_fragment_dir, delta);
	add_vector(&second_fragment.position, second_fragment_dir);

	PhysicsBody third_fragment;
	third_fragment.collider.points_count = 2;
	third_fragment.collider.points[0] = player.body.collider.points[2];
	third_fragment.collider.points[1] = player.body.collider.points[0];
	third_fragment.position = player.body.position;

	Vector third_fragment_dir = player.body.collider.points[2];
	normalise_vector(&third_fragment_dir);
	mul_vector(&third_fragment_dir, delta);
	add_vector(&third_fragment.position, third_fragment_dir);

	draw_physics_body(surface, first_fragment);
	draw_physics_body(surface, second_fragment);
	draw_physics_body(surface, third_fragment);
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

void draw_logo()
{
	draw_image_coord(get_logo_image(), (Vector) { 40, 100 });
}

void draw_instruction()
{
	draw_image_coord(get_instruction_image(), (Vector) { 180, 400 });
}