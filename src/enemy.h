#pragma once

#include "physicsbody.h"
#include "vector.h"
#include "randomizer.h"

#define MAX_ENEMIES 32

typedef struct
{
	bool alive;
	int size;
	int body_type;
	PhysicsBody body;
	/* ... */
} Enemy;

void enemy_init(Enemy *enemy, Vector position, Vector direction, double velocity, int body_type, int size);

void enemies_init(Enemy enemies[], int n);

int enemy_boom(Enemy *shoted_enemy, Enemy enemies[]);

void enemy_remove(Enemy *enemy);

bool enemy_collision_with(Enemy enemy, PhysicsBody body);
