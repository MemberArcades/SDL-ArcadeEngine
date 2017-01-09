#include "game.h"

#include "window.h"
#include "renderer.h"
#include "input.h"
#include "movement.h"
#include "block.h"
#include "fieldnextblock.h"
#include "randomizer.h"
#include "gamescore.h"
#include "music.h"
#include "main.h"

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

		move_down();

		destroy_full_line();

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
	init_game_score();

	draw_text("Press plus or minus", (Point) { 360, 200 });
	draw_text("to music.", (Point) { 400, 218 });

	*get_sum_boost() = 0;

	game->game_state = GamePlayState;
}

bool game_over(Game *game)
{
	if (!*get_opportun_create_blocks())
	{
		draw_image_coord(get_game_over_image(), (Point) { 23, 101 });

		check_high_score();

		return true;
	}
	else
	{
		return false;
	}
}

bool game_delay()
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

