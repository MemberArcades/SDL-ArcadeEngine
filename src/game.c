#include "game.h"

#include <math.h>

#include "window.h"
#include "renderer.h"
#include "player.h"
#include "enemy.h"
#include "input.h"

static void process_player(Game *game);

static void process_bullets(Bullet *bullets);

static void process_enemies(Game *game);

/* Кол-во астероидов на уровне */
static int waves[5] = {3, 5, 8, 13, 21};

void game_tick(Game *game)
{
	switch (game->game_state)
	{
	case GameBeginState:
		break;

	case GamePlayState:
		process_player(game);
		process_enemies(game);

		break;

	case GameOverState:
		break;
	}
}

void game_render(Game *game)
{
	switch (game->game_state)
	{
	case GameBeginState:
		break;

	case GamePlayState:
		draw_player(get_screen(), game->player);

		for (int i = 0; i < MAX_ENEMIES; ++i)
			draw_enemy(get_screen(), game->enemy[i]);

		break;

	case GameOverState:
		break;
	}
}

void game_init(Game *game)
{
	game->lvl = 0;

	player_init(&game->player);

	enemies_init(game->enemy, waves[game->lvl]);
	game->enemies_count = waves[game->lvl];

	game->game_state = GamePlayState;
}

static void process_player(Game *game)
{
	Player *player = &game->player;

	player->thrust = false;

	if (key_held(SDLK_UP))
		player->thrust = true;

	if (key_held(SDLK_LEFT))
		rotate_player(player, -2.0);

	if (key_held(SDLK_RIGHT))
		rotate_player(player, 2.0);

	if (key_held(SDLK_x))
		player_shoot(player);

	/* Передвижение */
	if (player->thrust)
	{ 
		Vector punch = { 0, 1 };
		rotate_vector(&punch, player->angle);
		mul_vector(&punch, 0.2);

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

	/* Пули */
	process_bullets(&player->bullets);

	inf_screen(&player->body);
}

static void process_bullets(Bullet *bullets)
{
	for (int i = 0; i < MAX_BULLETS; ++i)
	{
		Bullet *bullet = &bullets[i];

		if (!bullet->alive)
		{
			continue;
		}

		add_vector(&bullet->body.position, bullet->body.direction);

		inf_screen(&bullet->body);

		unsigned cur_time = SDL_GetTicks();
		if (cur_time - bullet->shoot_time > 1000)
		{
			bullet_remove(bullet);
		}
	}
}

static void process_enemies(Game *game)
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		Enemy *enemy = &game->enemy[i];

		if (!enemy->alive)
			continue;

		add_vector(&enemy->body.position, enemy->body.direction);

		inf_screen(&enemy->body);

		/* Столкновение с игроком */
		if (enemy_collision_with(*enemy, game->player.body))
		{
			enemy_remove(enemy);
			--game->enemies_count;
		}

		/* Столкновение с пулями */
		for (int j = 0; j < MAX_BULLETS; ++j)
		{
			Bullet *bullet = &game->player.bullets[j];

			if (!bullet->alive)
			{
				continue;
			}

			if (enemy_collision_with(*enemy, bullet->body))
			{
				bullet_remove(bullet);

				enemy_remove(enemy);
				--game->enemies_count;
			}
		}
	}

	/* Новый уровень */
	if (game->enemies_count < 1)
	{
		printf("%d\n", game->lvl);
		if (game->lvl < 4)
			++game->lvl;
		
		int new_wave = waves[game->lvl];
		enemies_init(game->enemy, new_wave);
		game->enemies_count = new_wave;
	}
}
