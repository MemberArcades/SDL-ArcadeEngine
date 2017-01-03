#include "game.h"

#include "window.h"
#include "renderer.h"
#include "input.h"
#include "movement.h"
#include "block.h"

static int delaySize = 0;

void game_tick(Game *game)
{
	switch (game->game_state)
	{
	case GameBeginState:
		break;

	case GamePlayState:
		if (!check_movement())
		{
			generation_random_block();
		}

		key_rotation();
		movement_dir_button();
		move_toward(Down);
		destroy_full_line(game);

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
		
		break;

	case GameOverState:
		break;
	}
}

void game_init(Game *game)
{
	draw_background();
	init_main_field();
	init_keys_state();
	init_generation_block();

	game->game_state = GamePlayState;
	game->game_score = 0;
}

bool game_over(Game *game)
{
	if (!*get_opportun_create_blocks())
	{
		draw_image_coord(get_game_over_image(), (Point) { 23, 101 });

		return true;
	}
	else
	{
		return false;
	}
}

void game_quit()
{
	destroy_image();
}

bool gmae_delay()
{
	if (delaySize <= 100)
	{
		++delaySize;

		return false;
	}
	else
	{
		delaySize = 0;

		return true;
	}
}