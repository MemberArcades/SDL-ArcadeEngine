#pragma once

#include "physicsbody.h"

typedef struct
{
	bool alive;
	int size;
	PhysicsBody body;
	/* ... */
} Enemy;

void enemy_init(Enemy *enemy, Vector position, Vector direction, double velocity, int body_type);

void enemies_init(Enemy enemies[], int n);

void enemy_reset_to_position(Enemy enemies[], Vector position);

void enemy_remove(Enemy enemies[], int number);