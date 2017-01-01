#include "physicsbody.h"

void move_physics_body(PhysicsBody *body)
{
	Vector move_vector = body->direction;
	mul_vector(&move_vector, body->velocity);

	add_vector(&body->position, move_vector);
}

void rotate_collider(PhysicsBody *body, double degrees)
{
	for (int i = 0; i < body->collider.points_count; i++)
	{
		rotate_vector(&body->collider.points[i], degrees);
	}
}

void rotate_physics_body(PhysicsBody *body, double degrees)
{
	rotate_vector(&body->direction, degrees);

	rotate_collider(body, degrees);
}

void inf_screen(PhysicsBody *body)
{
	double x = body->position.x;
	double y = body->position.y;

	if (x < 0)
		body->position.x = SCREEN_WIDTH;
	if (x > SCREEN_WIDTH)
		body->position.x = 0;
	if (y < 0)
		body->position.y = SCREEN_HEIGHT;
	if (y > SCREEN_HEIGHT)
		body->position.y = 0;
}