#include "game.h"

#include "window.h"
#include "renderer.h"
#include "input.h"
#include "movement.h"
#include "block.h"
#include "fieldnextblock.h"
#include "randomizer.h"

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
			unpress_keys();
			generation_random_block();
		}

		key_rotation();
		movement_dir_button();

		move_down();
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
	*get_sum_boost() = 0;

	game->game_state = GamePlayState;
	game->game_score = 0;

	printf("You score: %d\n", game->game_score);
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

void add_game_score(Game *game, int score)
{
	game->game_score += score;

	if (game->game_score > game->high_score)
	{
		game->high_score = game->game_score;
	}
}

void game_init_score(Game *game)
{
	game->high_score = 0;
}