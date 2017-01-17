#include "rotation.h"

#include "block.h"
#include "fieldnextblock.h"
#include "figure.h"


static BlockState stateRotation;


static void rotation_line(Direction direction, BlockColor blockColor, int i, int j);

static void rotation_jt(Direction direction, BlockColor blockColor, int i, int j, BlockType blockType);


BlockState* get_state_rotation()
{
	return &stateRotation;
}

static void rotation_line(Direction direction, BlockColor blockColor, int i, int j)
{
	switch (direction)
	{
	case Up:
	case Down:
		if (check_create(i, j, i, j + 3))
		{
			create_line(BackgroundColor, Background, i, j, Up);
			create_line(blockColor, Moves, i, j, Right);

			stateRotation.direction = Right;
		}

		break;
	case Right:
	case Left:
		for (int k = 0; k < 4; ++k)
		{
			if (check_create(i - k, j, i - k + 3, j))
			{
				create_line(BackgroundColor, Background, i, j, Right);
				create_line(blockColor, Moves, i - k, j, Up);

				stateRotation.i -= k;
				stateRotation.direction = Up;

				break;
			}
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

void rotation()
{
	switch (stateRotation.type)
	{
	case Square:
		break;
	case Line:
		rotation_line(stateRotation.direction, stateRotation.color, stateRotation.i, stateRotation.j);
		break;
	case JL:
	case JR:
	case T:
	case NL:
	case NR:
		rotation_jt(stateRotation.direction, stateRotation.color, stateRotation.i, stateRotation.j, stateRotation.type);
		break;
	}
}

static void rotation_jt(Direction direction, BlockColor blockColor, int i, int j, BlockType blockType)
{
	switch (direction)
	{
	case Up:
		for (int k = 0; k < 2; ++k)
		{
			if (check_create(i + k, j, i + 1 + k, j + 2))
			{
				if (create_jt(BackgroundColor, Background, i, j, Up, blockType))
				{
					create_jt(blockColor, Moves, i + k, j, Right, blockType);

					stateRotation.i += k;
					stateRotation.direction = Right;

					break;
				}
			}
		}

		break;
	
	case Right:
		for (int k = 0; k < 2; ++k)
		{
			if (check_create(i - k, j, i + 2 - k, j + 1))
			{
				if (create_jt(BackgroundColor, Background, i, j, Right, blockType))
				{
					create_jt(blockColor, Moves, i - k, j, Down, blockType);

					stateRotation.i -= k;
					stateRotation.direction = Down;

					break;
				}
			}
		}

		break;
	
	case Down:
		for (int k = 0; k < 2; ++k)
		{
			if (check_create(i + k, j, i + 1 + k, j + 2))
			{
				if (create_jt(BackgroundColor, Background, i, j, Down, blockType))
				{
					create_jt(blockColor, Moves, i + k, j, Left, blockType);

					stateRotation.i += k;
					stateRotation.direction = Left;

					break;
				}
			}
		}

		break;
	
	case Left:
		for (int k = 0; k < 2; ++k)
		{
			if (check_create(i - k, j, i + 2 - k, j + 1))
			{
				if (create_jt(BackgroundColor, Background, i, j, Left, blockType))
				{
					create_jt(blockColor, Moves, i - k, j, Up, blockType);

					stateRotation.i -= k;
					stateRotation.direction = Up;

					break;
				}
			}
		}

		break;
	}
}