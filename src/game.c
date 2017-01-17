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


void game_tick(Game *game)
{
	if (game->game_state == GamePlayState)
	{
		if (!check_movement())
		{
			unpress_keys();
			generation_random_block();
		}

		move_down();

		destroy_full_line();
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

	draw_text("Press c to swap", (Point) { 360, 270 });
	draw_text("texture.", (Point) { 400, 288 });

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