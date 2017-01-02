#include "game.h"

#include "window.h"
#include "renderer.h"
#include "input.h"
#include "movement.h"
#include "block.h"

void game_tick(Game *game)
{
	switch (game->game_state)
	{
	case GameBeginState:
		break;

	case GamePlayState:
		if (!check_movement())
		{
			generation_blocks(BlueColor, Square);
		}

		movement_dir_button();
		//move_toward(Down);

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

	game->game_state = GamePlayState;
}

bool game_over(Game *game)
{
	if (!check_opportunity_create_block())
	{
		draw_image_coord(get_game_over_image(), (Point) { 23, 101 });

		return true;
	}
	else
	{
		return false;
	}
}