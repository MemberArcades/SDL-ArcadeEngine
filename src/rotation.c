#include "rotation.h"

extern BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];

static BlockState stateRotation;

static void rotation_line();

static bool check_rotation_line();

static void block_rotation();


BlockState* get_state_rotation()
{
	return &stateRotation;
}

static void block_rotation()
{
	switch (stateRotation.type)
	{
	case Square:
		break;
	case Line:
		rotation_line();
		break;
	}
}

static void rotation_line()
{
	if (check_rotation_line())
	{
		if ((stateRotation.direction == Up) || (stateRotation.direction == Down))
		{
			for (int k = 0; k < 5; ++k)
			{
				recolor_block_main_field(BackgroundColor, Background, stateRotation.i + k, stateRotation.j);
				recolor_block_main_field(stateRotation.color, Moves, stateRotation.i, stateRotation.j + k);
			}

			stateRotation.direction = Right;
			
		}
		else
		{
			for (int k = 0; k < 5; ++k)
			{
				recolor_block_main_field(BackgroundColor, Background, stateRotation.i, stateRotation.j + k);
				recolor_block_main_field(stateRotation.color, Moves, stateRotation.i + k, stateRotation.j);
			}

			stateRotation.direction = Up;
		}
	}
}

static bool check_rotation_line()
{
	switch (stateRotation.direction)
	{
	case Up:
	case Down:
	{
		/*int size = 0;
		for (int k = 0; (stateRotation.j + k < Y_MAIN_FIELD_SIZE) && (size <= 3); ++k)
		{
			if (size == 3)
			{
				return true;
			}

			if (mainField[stateRotation.i][stateRotation.j + k].status == Background)
			{
				++size;
			}
			else
			{
				size = 0;
			}
		}

		return false;*/
		for (int k = 0; stateRotation.j + k < Y_MAIN_FIELD_SIZE; ++k)
		{
			if ((mainField[stateRotation.i][stateRotation.j + k].status != Background) && (mainField[stateRotation.i][stateRotation.j + k].status != Moves))
			{
				return false;
			}

			if (k == 4)
			{
				return true;
			}
		}

		break;
	}
	case Right:
	case Left:
	{
		/*int size = 0;

		for (int k = 0; (stateRotation.i + k < X_MAIN_FIELD_SIZE) && (size <= 3); ++k)
		{
			if (size == 3)
			{
				return true;
			}

			if (mainField[stateRotation.i + k][stateRotation.j].status == Background)
			{
				++size;
			}
			else
			{
				size = 0;
			}
		}

		return false;*/
		for (int k = 0; stateRotation.i + k < X_MAIN_FIELD_SIZE; ++k)
		{
			if ((mainField[stateRotation.i + k][stateRotation.j].status != Background) && (mainField[stateRotation.i + k][stateRotation.j].status != Moves))
			{
				return false;
			}

			if (k == 4)
			{
				return true;
			}
		}

		break;
	}
	}

	return false;
}

void key_rotation()
{
	if (key_held(SDLK_SPACE) == KeyDown)
	{
		handle_keydown(SDLK_SPACE);

		block_rotation();
	}
}