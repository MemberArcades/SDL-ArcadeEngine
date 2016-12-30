#pragma once

#include "physicsbody.h"

typedef struct
{
	PhysicsBody body;
	/* ... */
} Player;

void player_init(Player *player);

void player_move(Player *player, double pwr);
