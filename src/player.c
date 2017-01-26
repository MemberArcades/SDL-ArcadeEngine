#include "player.h"
#include "input.h"
#include "vector.h"

void player_init(Player *player)
{
	player->body.position = (Vector) { 15, 15 };
	player->body.direction = (Vector) { 0, 1 };
	player->body.velocity = 0;
}
