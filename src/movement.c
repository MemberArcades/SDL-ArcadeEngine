#include "movement.h"
#include "input.h"

extern BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];

static bool check_move(Direction direction);

static Direction get_movement_dir_button();

static void dir_move(Move *move, Direction direction);

bool check_movement()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			if (mainField[i][j].status == Moves)
			{
				return true;
			}
		}
	}

	return false;
}

static void dir_move(Move *move, Direction direction)
{
	switch (direction)
	{
	case Up:
		move->u = 1;
		break;
	case Right:
		move->r = 1;
		break;
	case Down:
		move->d = 1;
		break;
	case Left:
		move->l = 1;
		break;
	}
}

static bool check_move(Direction direction)
{
	Move move = { 0, 0, 0, 0 };
	dir_move(&move, direction);

	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			if ((mainField[i][j].status == Moves) &&
				((i - move.l < 0) || (i + move.r > X_MAIN_FIELD_SIZE - 1) || (j - move.u < 0) || (j + move.d > Y_MAIN_FIELD_SIZE - 1) ||
				((mainField[i + move.r - move.l][j + move.d - move.u].status != Moves) &&
				(mainField[i + move.r - move.l][j + move.d - move.u].status != Background))))
			{
				printf("%d %d move: %d %d %d %d;\n ", i, j, move.u, move.r, move.d, move.l);
				return false;
			}
		}
	}

	return true;
}

void move_toward(Direction direction)
{
	if (check_move(direction))
	{
		Move move = { 0, 0, 0, 0 };
		dir_move(&move, direction);

		switch (direction)
		{
		case Up:
		case Left:
			for (int i = move.l; i < X_MAIN_FIELD_SIZE; ++i)
			{
				for (int j = move.u; j < Y_MAIN_FIELD_SIZE; ++j)
				{
					if (mainField[i][j].status == Moves)
					{
						recolor_block_main_field(mainField[i][j].color, Moves, i - move.l, j - move.u);
						recolor_block_main_field(BackgroundColor, Background, i, j);
					}
				}
			}

			break;
		case Right:
		case Down:
			for (int i = X_MAIN_FIELD_SIZE - 1 - move.r; i >= 0; --i)
			{
				for (int j = Y_MAIN_FIELD_SIZE - 1 - move.d; j >= 0; --j)
				{
					if (mainField[i][j].status == Moves)
					{
						recolor_block_main_field(mainField[i][j].color, Moves, i + move.r, j + move.d);
						recolor_block_main_field(BackgroundColor, Background, i, j);
					}
				}
			}

			break;
		}
	}

	if (!check_move(Down))
	{
		moves_to_basis();
	}
}

static Direction get_movement_dir_button()
{
	if (key_held(SDLK_w) || key_held(SDLK_UP))
	{
		printf("Up pressed\n");
		return Up;
	}

	if (key_held(SDLK_d) || key_held(SDLK_RIGHT))
	{
		printf("Right pressed\n");
		return Right;
	}

	if (key_held(SDLK_a) || key_held(SDLK_LEFT))
	{
		printf("Left pressed\n");
		return Left;
	}

	if (key_held(SDLK_s) || key_held(SDLK_DOWN))
	{
		printf("Down pressed\n");
		return Down;
	}

	printf("get_movement_dir_button Error\n");
	exit(1);
}

void movement_dir_button()
{
	if (check_key_movement_pressed())
	{
		move_toward(get_movement_dir_button());
	}
}