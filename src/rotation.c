#include "rotation.h"
#include "block.h"
#include "fieldnextblock.h"
#include "figure.h"

static BlockState stateRotation;


static void block_rotation();

static void rotation_line();

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
	int i = stateRotation.i;
	int j = stateRotation.j;

	switch (stateRotation.direction)
	{
	case Up:
	case Down:
		if (check_create(i, j, i, j + 3))
		{
			create_line(BackgroundColor, Background, i, j, Up);
			create_line(stateRotation.color, Moves, i, j, Right);

			stateRotation.direction = Right;
		}

		break;
	case Right:
	case Left:
		if (check_create(i, j, i + 3, j))
		{
			create_line(BackgroundColor, Background, i, j, Right);
			create_line(stateRotation.color, Moves, i, j, Up);

			stateRotation.direction = Up;
		}

		break;
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
	int i = stateRotation.i;
	int j = stateRotation.j;

	switch (stateRotation.direction)
	{
	case Up:
	{
		if (check_create(i, j, i + 1, j + 2))
		{
			create_j_l(BackgroundColor, Background, i, j, Up);
			create_j_l(stateRotation.color, Moves, i, j, Right);

			stateRotation.direction = Right;
		}

		break;
	}
	case Right:
	{
		if (check_create(i, j, i + 2, j + 1))
		{
			create_j_l(BackgroundColor, Background, i, j, Right);
			create_j_l(stateRotation.color, Moves, i, j, Down);

			stateRotation.direction = Down;
		}

		break;
	}
	case Down:
	{
		if (check_create(i, j, i + 1, j + 2))
		{
			create_j_l(BackgroundColor, Background, i, j, Down);
			create_j_l(stateRotation.color, Moves, i, j, Left);

			stateRotation.direction = Left;
		}

		break;
	}
	case Left:
	{
		if (check_create(i, j, i + 2, j + 1))
		{
			create_j_l(BackgroundColor, Background, i, j, Left);
			create_j_l(stateRotation.color, Moves, i, j, Up);

			stateRotation.direction = Up;
		}

		break;
	}
	}
}

static void rotation_j_r()
{
	int i = stateRotation.i;
	int j = stateRotation.j;

	switch (get_state_rotation()->direction)
	{
	case Up:
		if (check_create(i, j, i + 1, j + 2))
		{
			create_j_r(BackgroundColor, Background, i, j, Up);	
			create_j_r(stateRotation.color, Moves, i, j, Right);

			stateRotation.direction = Right;
		}

		break;
	case Right:
		if (check_create(i, j, i + 2, j + 1))
		{
			create_j_r(BackgroundColor, Background, i, j, Right);
			create_j_r(stateRotation.color, Moves, i, j, Down);

			stateRotation.direction = Down;
		}

		break;
	case Down:
		if (check_create(i, j, i + 1, j + 2))
		{
			create_j_r(BackgroundColor, Background, i, j, Down);
			create_j_r(stateRotation.color, Moves, i, j, Left);

			stateRotation.direction = Left;
		}

		break;
	case Left:
		if (check_create(i, j, i + 2, j + 1))
		{
			create_j_r(BackgroundColor, Background, i, j, Left);
			create_j_r(stateRotation.color, Moves, i, j, Up);

			stateRotation.direction = Up;
		}

		break;
	}
}