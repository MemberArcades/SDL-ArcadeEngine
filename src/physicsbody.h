#pragma once

#include <stdbool.h>

#include "vector.h"
#include "main.h"

typedef struct
{
	Vector points[16];
	int  points_count;
} Collider;

typedef struct
{
	Vector position;
	Vector direction;
	Collider collider;
	double velocity;
} PhysicsBody;

void move_physics_body(PhysicsBody *body);

void rotate_physics_body(PhysicsBody *body, double degrees);

void inf_screen(PhysicsBody *body);