#include "rotation.h"
#include "block.h"
#include "fieldnextblock.h"
#include "figure.h"

static BlockState stateRotation;


static void block_rotation();

static void rotation_line();

static void rotation_j();


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
	case JR:
		rotation_j();
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

static void rotation_j()
{
	int i = stateRotation.i;
	int j = stateRotation.j;

	switch (stateRotation.direction)
	{
	case Up:
	{
		if (check_create(i, j, i + 1, j + 2))
		{
			create_j(BackgroundColor, Background, i, j, Up, stateRotation.type);
			create_j(stateRotation.color, Moves, i, j, Right, stateRotation.type);

			stateRotation.direction = Right;
		}

		break;
	}
	case Right:
	{
		if (check_create(i, j, i + 2, j + 1))
		{
			create_j(BackgroundColor, Background, i, j, Right, stateRotation.type);
			create_j(stateRotation.color, Moves, i, j, Down, stateRotation.type);

			stateRotation.direction = Down;
		}

		break;
	}
	case Down:
	{
		if (check_create(i, j, i + 1, j + 2))
		{
			create_j(BackgroundColor, Background, i, j, Down, stateRotation.type);
			create_j(stateRotation.color, Moves, i, j, Left, stateRotation.type);

			stateRotation.direction = Left;
		}

		break;
	}
	case Left:
	{
		if (check_create(i, j, i + 2, j + 1))
		{
			create_j(BackgroundColor, Background, i, j, Left, stateRotation.type);
			create_j(stateRotation.color, Moves, i, j, Up, stateRotation.type);

			stateRotation.direction = Up;
		}

		break;
	}
	}
}