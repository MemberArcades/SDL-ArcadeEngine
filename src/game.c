#include "game.h"

#include <math.h>

#include "window.h"
#include "renderer.h"
#include "player.h"
#include "input.h"

static void process_player(Game *game);

static void process_enemies(Game *game, int n);

void game_tick(Game *game)
{
	switch (game->game_state)
	{
	case GameBeginState:
		break;

	case GamePlayState:
		process_player(game);
		process_enemies(game, MAX_ENEMIES);

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
	player_init(&game->player);

	enemies_init(&game->enemy, MAX_ENEMIES);

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

	inf_screen(&player->body);
}

static void process_enemies(Game *game, int n)
{
	for (int i = 0; i < n; ++i)
	{
		Enemy *enemy = &game->enemy[i];

		if (!enemy->alive)
			continue;

		add_vector(&enemy->body.position, enemy->body.direction);

		inf_screen(&enemy->body);
	}
}
