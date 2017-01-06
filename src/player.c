#include "player.h"

void player_init(Player *player)
{
	player->alive = true;
	player->lives = 3;

	player->thrust = false;
	player->angle = 0;

	player->body.position = (Vector) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	player->body.direction = (Vector) { 0, 0 };
	player->body.velocity = 1;

	player->body.collider.points_count = 3;
	player->body.collider.points[0] = (Vector) { 0, 15 };
	player->body.collider.points[1] = (Vector) { 5, 0 };
	player->body.collider.points[2] = (Vector) { -5, 0 };

	bullets_init(player->bullets, MAX_BULLETS);
	player->last_bullet = SDL_GetTicks();

	player->last_jump = SDL_GetTicks();
}

void player_remove(Player *player)
{
	--player->lives;

	player->body.position = (Vector) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	player->body.direction = (Vector) { 0, 0 };
}

void player_movement(Player *player, double pwr)
{
	if (player->thrust)
	{
		Vector punch = { 0, 1 };
		rotate_vector(&punch, player->angle);
		mul_vector(&punch, pwr);

		add_vector(&player->body.direction, punch);
	}
	else {
		mul_vector(&player->body.direction, 0.99);
	}

	double max_speed = 2.1;
	double speed = sqrt(player->body.direction.x * player->body.direction.x + player->body.direction.y * player->body.direction.y);

	if (speed > max_speed)
	{
		mul_vector(&player->body.direction, max_speed / speed);
	}

	add_vector(&player->body.position, player->body.direction);
}

void rotate_player(Player *player, double degrees)
{
	player->angle += degrees;
	rotate_collider(&player->body, degrees);
}

void player_shoot(Player *player)
{
	unsigned cur_time = SDL_GetTicks();
	
	/* Ограничение скорострельности */
	if (cur_time - player->last_bullet < 300)
	{
		return;
	}

	Vector bullet_dir = { 0, 1 };
	rotate_vector(&bullet_dir, player->angle);

	bullet_shot(player->bullets, player->body.position, bullet_dir);

	player->last_bullet = cur_time;
}

void player_hyper_jump(Player *player)
{
	unsigned cur_time = SDL_GetTicks();

	/* пїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅпїЅ пїЅпїЅпїЅпїЅпїЅпїЅпїЅ */
	if (cur_time - player->last_jump < 1000)
	{
		return;
	}

	player->body.position = rand_pos();

	player->last_jump = cur_time;
}