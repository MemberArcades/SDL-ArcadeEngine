#include "figure.h"

extern BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];

static bool opportunityCreateBlock;


static bool check_create(int i0, int j0, int i1, int j1);

static void randomizer();


bool* get_opportun_create_blocks()
{
	return &opportunityCreateBlock;
}

bool generation_blocks(BlockColor blockColor, BlockType blockType, Direction direction)
{
	if (blockColor == RandomColor)
	{
		random_color(&blockColor);
	}

	if (blockType == RandomType)
	{
		random_type(&blockType);
	}

	if (direction == RandomDirection)
	{
		random_direction(&direction);
	}

	get_state_rotation()->direction = direction;
	get_state_rotation()->type = blockType;
	get_state_rotation()->color = blockColor;

	switch (blockType)
	{
	case Square:
		if (!create_square(blockColor, SQARE_SIZE, 4, 0))
		{
			*get_opportun_create_blocks() = false;

			return false;
		}

		get_state_rotation()->i = 4;
		get_state_rotation()->j = 0;

		break;
	case Line:
	{
		int i = 2;

		if ((direction == Right) || (direction == Left))
		{
			i += 2;
		}

		if (!create_line(blockColor, i, 0, direction))
		{
			*get_opportun_create_blocks() = false;

			return false;
		}

		get_state_rotation()->i = 2;
		get_state_rotation()->j = 0;

		break;
	}
	}

	return true;
}

bool create_square(BlockColor blockColor, int sqareSize, int i, int j)
{
	if ((0 <= i) && (i + sqareSize - 1 < X_MAIN_FIELD_SIZE) &&
		(0 <= j) && (j + sqareSize - 1 < Y_MAIN_FIELD_SIZE) &&
		check_create(i, j, i + sqareSize, j + sqareSize))
	{
		for (int x = 0; x < sqareSize; ++x)
		{
			for (int y = 0; y < sqareSize; ++y)
			{
				recolor_block_main_field(blockColor, Moves, i + x, j + y);
			}
		}
	}
}

bool create_line(BlockColor blockColor, int i, int j, Direction direction)
{
	switch (direction)
	{
	case Up:
	case Down:
		if ((0 <= i) && (i + 4 < X_MAIN_FIELD_SIZE) &&
			(0 <= j) && (j < Y_MAIN_FIELD_SIZE) &&
			check_create(i, j, i + 5, j))
		{
			for (int x = 0; x < 5; ++x)
			{
				recolor_block_main_field(blockColor, Moves, i + x, j);
			}

			return true;
		}

		break;
	case Right:
	case Left:
		if ((0 <= i) && (i < X_MAIN_FIELD_SIZE) &&
			(0 <= j) && (j + 4 < Y_MAIN_FIELD_SIZE) &&
			check_create(i, j, i, j + 5))
		{
			for (int y = 0; y < 5; ++y)
			{
				recolor_block_main_field(blockColor, Moves, i, j + y);
			}

			return true;
		}

		break;
	}

	return false;
}

static bool check_create(int i0, int j0, int i1, int j1)
{
	for (i0; i0 < i1; ++i0)
	{
		for (j0; j0 < j1; ++j0)
		{
			if (mainField[i0][j0].status != Background)
			{
				opportunityCreateBlock = false;

				return false;
			}
		}
	}

	return true;
}