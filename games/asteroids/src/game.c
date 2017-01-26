#include "game.h"

static void process_player(Player *player);

static void process_bullets(Bullet bullets[]);

static void process_enemies(Game *game);

void game_tick(Game *game)
{
	switch (game->game_state)
	{
	case GameBeginState:
		enemies_init(game->enemy, ENEMIES);
		game->enemies_count = ENEMIES;

		process_player(&game->player);

		if (SDL_GetTicks() - game->last_gamestate_change > 1400)
		{
			game->game_state = GamePlayState;
			game->last_gamestate_change = SDL_GetTicks();
		}

		break;

	case GamePlayState:
		process_player(&game->player);
		process_enemies(game);

		break;

	case GameDeathState:
		/* Обработка столкновений и управленияна время отключаются */
		process_enemies(game);

		if (SDL_GetTicks() - game->last_gamestate_change > 2000)
		{
			if (game->player.lives <= 0)
			{ 
				game->game_state = GameOverState;
			}
			else
			{ 
				player_remove(&game->player);

				game->game_state = GamePlayState;
				game->last_gamestate_change = SDL_GetTicks();
			}
		}

		break;

	case GameOverState:
		exit(0);

		break;
	}
}

void game_render(Game *game)
{
	switch (game->game_state)
	{
	case GameBeginState:
		draw_hud(get_screen(), game->player);
		draw_player(get_screen(), game->player);	

		break;

	case GamePlayState:
		draw_hud(get_screen(), game->player);
		draw_player(get_screen(), game->player);

		for (int i = 0; i < MAX_ENEMIES; ++i)
			draw_enemy(get_screen(), game->enemy[i]);

		break;

	case GameDeathState:
		/* Анимация поломки корабля, отрисовка врагов не прекращается */
		draw_hud(get_screen(), game->player);
		draw_player_crash(get_screen(), game->player);

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
	game->score = 0;
	game->game_state = GameBeginState;
	game->last_gamestate_change = SDL_GetTicks();
	
	player_init(&game->player);
}

static void process_player(Player *player)
{
	player->thrust = false;

	if (key_held(SDLK_UP))
		player->thrust = true;

	if (key_held(SDLK_LEFT))
		rotate_player(player, -2.0);

	if (key_held(SDLK_RIGHT))
		rotate_player(player, 2.0);

	if (key_held(SDLK_x))
		player_shoot(player);

	if (key_held(SDLK_c))
		player_hyper_jump(player);

	/* Передвижение */
	player_movement(player, 0.2);

	process_bullets(player->bullets);

	inf_screen(&player->body);
}

static void process_bullets(Bullet bullets[])
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

		Vector temp = enemy->body.direction;
		mul_vector(&temp, enemy->body.velocity);

		add_vector(&enemy->body.position, temp);

		inf_screen(&enemy->body);

		/* Столкновение с игроком */
		if (enemy_collision_with(*enemy, game->player.body) && game->game_state == GamePlayState)
		{
			game->last_gamestate_change = SDL_GetTicks();
			game->player.crash_time = SDL_GetTicks();
			game->game_state = GameDeathState;
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
				
				if (enemy->size == 3)
					game->score += 20;
				else if (enemy->size == 2)
					game->score += 50;
				else if (enemy->size == 1)
					game->score += 100;

				printf("Score: %d\n", game->score);

				game->enemies_count += enemy_boom(enemy, game->enemy);
			}
		}
	}

	/* Новый уровень */
	if (game->enemies_count < 1)
	{	
		game->game_state = GameBeginState;
		game->last_gamestate_change = SDL_GetTicks();
	}
}
