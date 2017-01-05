#pragma once

#include <stdbool.h>
#include "SDL.h"

#include "player.h"
#include "enemy.h"
#include "vector.h"

void draw_image_coord(SDL_Surface *surface, Vector dst);

void draw_image_coord_offset(SDL_Surface *surface, Vector dst, Vector offset);

void draw_point(SDL_Surface *surface, Vector dst, Uint32 color);

void draw_line(SDL_Surface *surface, Vector begin, Vector end, Uint32 color);

void draw_player(SDL_Surface *surface, Player player);

void draw_enemy(SDL_Surface *surface, Enemy enemy);

void draw_bullet(SDL_Surface *surface, Bullet bullet);
