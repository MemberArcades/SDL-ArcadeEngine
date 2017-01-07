#include "block.h"

#include "imageloader.h"
#include "renderer.h"
#include "window.h"
#include "game.h"
#include "main.h"

#include <stdlib.h>


BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];


static bool check_full_line(int *y);


void init_main_field()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			mainField[i][j].color = BackgroundColor;
			mainField[i][j].status = Background;
		}
	}

	*get_opportun_create_blocks() = true;
}

BlockArr (* get_main_field())[Y_MAIN_FIELD_SIZE]
{
	return mainField;
}

void recolor_main_field()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			draw_block_offset(mainField[i][j].color, (Point) { i * 32, j * 32 }, (Point) { X_MAIN_FIELD, Y_MAIN_FIELD });
		}
	}
}

void recolor_block_main_field(BlockColor blockColor, BlockStatus blockStatus, int i, int j)
{
	mainField[i][j].color = blockColor;
	mainField[i][j].status = blockStatus;

	draw_block_offset(blockColor, (Point) { i * 32, j * 32 }, (Point) { X_MAIN_FIELD, Y_MAIN_FIELD });
}

void moves_to_basis()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			if (mainField[i][j].status == Moves)
			{
				mainField[i][j].status = Basis;
			}
		}
	}
}

static bool check_full_line(int *y)
{
	int line;

	for (int j = Y_MAIN_FIELD_SIZE - 1; j >= 0 ; --j)
	{
		line = 0;

		for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
		{
			if (mainField[i][j].status == Basis)
			{
				++line;
			}
		}

		if (line == X_MAIN_FIELD_SIZE)
		{
			*y = j;
			return true;
		}
	}

	return false;
}

void destroy_full_line(struct Game *game)
{
	int j;

	unsigned long long score = 100 + 100 * (*get_sum_boost());
	unsigned long long sumScore = 0;

	bool flag = false;

	while (check_full_line(&j))
	{
		flag = true;

		for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
		{
			recolor_block_main_field(BackgroundColor, Background, i, j);
		}

		blocks_to_moves(j);

		while (check_move(Down))
		{
			move_toward(Down);
		}

		moves_to_basis();

		add_game_score(score);

		sumScore += score;
		score += 100 + 100 * (*get_sum_boost());
	}

	if (flag)
	{
		printf("Added points: %llu, You score: %llu\n", sumScore, get_score()->current);
	}

}