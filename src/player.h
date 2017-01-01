#pragma once

#include "physicsbody.h"

typedef struct
{
	bool thrust;
	double angle;
	PhysicsBody body;
	/* ... */
} Player;

void player_init(Player *player);

void move_player(Player *player, double pwr);

void rotate_player(Player *player, double degrees);