#include "player.h"
#include "input.h"
#include "vector.h"

void player_init(Player *player)
{
	player->body.position = (Vector) { 15, 15 };
	player->body.direction = (Vector) { 0, 1 };
	player->body.velocity = 1;

	player->body.collider.points_count = 3;
	player->body.collider.points[0] = (Vector) { -5, 0 };
	player->body.collider.points[1] = (Vector) { 5, 0 };
	player->body.collider.points[2] = (Vector) { 0, 15 };
}

void move_player(Player *player, double pwr)
{
	move_physics_body(&player->body);
}

void rotate_player(Player *player, double degrees)
{
	rotate_physics_body(&player->body, degrees);
}