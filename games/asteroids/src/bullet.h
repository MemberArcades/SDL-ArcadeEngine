#pragma once

#include "SDL.h"
#include "physicsbody.h"

#define MAX_BULLETS 16

typedef struct
{
	bool alive;
	unsigned shoot_time;
	PhysicsBody body;
} Bullet;

void bullet_init(Bullet *bullet, double velocity);

void bullets_init(Bullet bullets[], int n);

void bullet_shot(Bullet bullets[], Vector pos, Vector dir);

void bullet_remove(Bullet *bullet);