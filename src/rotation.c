#include "rotation.h"

extern BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];

static BlockState stateRotation;

static void rotation_line();

static bool check_rotation_line();

static void block_rotation();

static void rotation_j_l();

static void rotation_j_r();


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
	case JL:
		rotation_j_l();
		break;
	case JR:
		rotation_j_r();
		break;
	}
}

static void rotation_line()
{
	if (check_rotation_line())
	{
		if ((stateRotation.direction == Up) || (stateRotation.direction == Down))
		{
			for (int k = 0; k < 4; ++k)
			{
				recolor_block_main_field(BackgroundColor, Background, stateRotation.i + k, stateRotation.j);
				recolor_block_main_field(stateRotation.color, Moves, stateRotation.i, stateRotation.j + k);
			}

			stateRotation.direction = Right;
			
		}
		else
		{
			for (int k = 0; k < 4; ++k)
			{
				recolor_block_main_field(BackgroundColor, Background, stateRotation.i, stateRotation.j + k);
				recolor_block_main_field(stateRotation.color, Moves, stateRotation.i + k, stateRotation.j);
			}

			stateRotation.direction = Up;
		}
	}
}

void reboot_rotatoin_index(Direction direction)
{
	switch (direction)
	{
	case Up:
		stateRotation.j -= 1;
		break;
	case Right:
		stateRotation.i += 1;
		break;
	case Down:
		stateRotation.j += 1;
		break;
	case Left:
		stateRotation.i -= 1;
		break;
	}
}

static bool check_rotation_line()
{
	switch (stateRotation.direction)
	{
	case Up:
	case Down:
	{
		for (int k = 0; stateRotation.j + k < Y_MAIN_FIELD_SIZE; ++k)
		{
			if ((mainField[stateRotation.i][stateRotation.j + k].status != Background) && (mainField[stateRotation.i][stateRotation.j + k].status != Moves))
			{
				return false;
			}

			if (k == 3)
			{
				return true;
			}
		}

		break;
	}
	case Right:
	case Left:
	{
		for (int k = 0; stateRotation.i + k < X_MAIN_FIELD_SIZE; ++k)
		{
			if ((mainField[stateRotation.i + k][stateRotation.j].status != Background) && (mainField[stateRotation.i + k][stateRotation.j].status != Moves))
			{
				return false;
			}

			if (k == 3)
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

static void rotation_j_l()
{
	switch (get_state_rotation()->direction)
	{
	case Up:
		if (create_j_l(get_state_rotation()->color, get_state_rotation()->i, get_state_rotation()->j, Right))
		{
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 1, get_state_rotation()->j + 1);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 2, get_state_rotation()->j + 1);

			get_state_rotation()->direction = Right;
		}

		break;
	case Right:
		if (create_j_l(get_state_rotation()->color, get_state_rotation()->i, get_state_rotation()->j, Down))
		{
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i, get_state_rotation()->j + 1);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 1, get_state_rotation()->j + 1);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i, get_state_rotation()->j + 2);

			get_state_rotation()->direction = Down;
		}

		break;
	case Down:
		if (create_j_l(get_state_rotation()->color, get_state_rotation()->i, get_state_rotation()->j, Left))
		{
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i, get_state_rotation()->j);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 2, get_state_rotation()->j);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 2, get_state_rotation()->j + 1);

			get_state_rotation()->direction = Left;
		}

		break;
	case Left:
		if (create_j_l(get_state_rotation()->color, get_state_rotation()->i, get_state_rotation()->j, Up))
		{
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i, get_state_rotation()->j + 2);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 1, get_state_rotation()->j);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 1, get_state_rotation()->j + 2);		

			get_state_rotation()->direction = Up;
		}

		break;
	}
}

static void rotation_j_r()
{
	
	switch (get_state_rotation()->direction)
	{
	case Up:
		if (create_j_r(get_state_rotation()->color, get_state_rotation()->i, get_state_rotation()->j, Right))
		{
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 2, get_state_rotation()->j);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 2, get_state_rotation()->j + 1);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 1, get_state_rotation()->j + 1);

			get_state_rotation()->direction = Right;
		}

		break;
	case Right:
		if (create_j_r(get_state_rotation()->color, get_state_rotation()->i, get_state_rotation()->j, Down))
		{
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i, get_state_rotation()->j + 2);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 1, get_state_rotation()->j + 2);

			get_state_rotation()->direction = Down;
		}

		break;
	case Down:
		
		if (create_j_r(get_state_rotation()->color, get_state_rotation()->i, get_state_rotation()->j, Left))
		{
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i, get_state_rotation()->j + 1);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 2, get_state_rotation()->j);

			get_state_rotation()->direction = Left;
		}

		break;
	case Left:
		if (create_j_r(get_state_rotation()->color, get_state_rotation()->i, get_state_rotation()->j, Up))
		{
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i, get_state_rotation()->j);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 1, get_state_rotation()->j);
			recolor_block_main_field(BackgroundColor, Background, get_state_rotation()->i + 1, get_state_rotation()->j + 2);

			get_state_rotation()->direction = Up;
		}

		break;
	}
}