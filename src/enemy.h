#pragma once

#include "physicsbody.h"

typedef struct
{
	PhysicsBody body;
	/* ... */
} Enemy;

void enemy_init(Enemy *enemy, Vector position, Vector direction, double velocity);

void enemies_init(Enemy enemies[], int n);