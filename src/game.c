#include "game.h"

#include "window.h"
#include "renderer.h"
#include "player.h"
#include "input.h"

static void process_player(Game *game);

void game_tick(Game *game)
{
	switch (game->game_state)
	{
	case GameBeginState:
		break;

	case GamePlayState:
		process_player(game);

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

		break;

	case GameOverState:
		break;
	}
}

void game_init(Game *game)
{
	player_init(&game->player);

	game->game_state = GamePlayState;
}

static void process_player(Game *game)
{
	Player *player = &game->player;

	if (key_held(SDLK_UP))
		add_vector(&player->body.position, player->body.direction);

	if (key_held(SDLK_LEFT))
		rotate_vector(&player->body.direction, -1);

	if (key_held(SDLK_RIGHT))
		rotate_vector(&player->body.direction, 1);
}
