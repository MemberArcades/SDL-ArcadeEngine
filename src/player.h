#pragma once

#include "physicsbody.h"
#include "bullet.h"
#include "input.h"
#include "vector.h"

typedef struct
{
	bool thrust;
	double angle;
	PhysicsBody body;

	Bullet bullets[MAX_BULLETS];
	unsigned last_bullet;

	unsigned last_jump;
} Player;

void player_init(Player *player);

void move_player(Player *player, double pwr);

void rotate_player(Player *player, double degrees);

void player_hyper_jump(Player *player);