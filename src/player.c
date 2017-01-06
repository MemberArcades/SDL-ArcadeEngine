#include "player.h"

void player_init(Player *player)
{
	player->thrust = false;
	player->angle = 0;

	player->body.position = (Vector) { 150, 150 };
	player->body.direction = (Vector) { 0, 1 };
	player->body.velocity = 1;

	player->body.collider.points_count = 3;
	player->body.collider.points[0] = (Vector) { 0, 15 };
	player->body.collider.points[1] = (Vector) { 5, 0 };
	player->body.collider.points[2] = (Vector) { -5, 0 };

	bullets_init(player->bullets, MAX_BULLETS);
	player->last_bullet = SDL_GetTicks();

	player->last_jump = SDL_GetTicks();
}

void move_player(Player *player, double pwr)
{
	move_physics_body(&player->body);
}

void rotate_player(Player *player, double degrees)
{
	player->angle += degrees;
	rotate_collider(&player->body, degrees);
}

void player_shoot(Player *player)
{
	unsigned cur_time = SDL_GetTicks();
	
	/* ����������� ���������������� */
	if (cur_time - player->last_bullet < 300)
	{
		return;
	}

	Vector bullet_dir = { 0, 1 };
	rotate_vector(&bullet_dir, player->angle);

	bullet_shot(player->bullets, player->body.position, bullet_dir);

	player->last_bullet = cur_time;

void player_hyper_jump(Player *player)
{
	unsigned cur_time = SDL_GetTicks();

	/* ����������� ������� */
	/* ����������� ������� */
	if (cur_time - player->last_jump < 1000)
	{
		return;
	}

	player->body.position = rand_pos();

	player->last_jump = cur_time;
}