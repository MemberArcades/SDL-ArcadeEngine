#include "figure.h"

extern BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];

static bool check_create(int i0, int j0, int i1, int j1);

static bool opportunityCreateBlock;

bool* get_opportun_create_blocks()
{
	return &opportunityCreateBlock;
}

void generation_blocks(BlockColor blockColor, BlockType blockType)
{
	if (blockColor == RandomColor)
	{
		blockColor = rand() % NUMBER_OF_COLORS + 2;
	}

	if (blockType == RandomType)
	{
		blockType = rand() % NUMBER_OF_TYPE + 1;
	}

	get_state_rotation()->direction = Up;
	get_state_rotation()->type = blockType;

	switch (blockType)
	{
	case Square:
		create_square(blockColor, SQARE_SIZE, 4, 0);
		break;
	case Line:
		create_line(blockColor, 2, 0);
		break;
	}
}

void create_square(BlockColor blockColor, int sqareSize, int i, int j)
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

void create_line(BlockColor blockColor, int i, int j)
{
	if ((0 <= i) && (i + 4 < X_MAIN_FIELD_SIZE) &&
		(0 <= j) && (j < Y_MAIN_FIELD_SIZE) &&
		check_create(i, j, i + 5, j))
	{
		for (int x = 0; x < 5; ++x)
		{
			recolor_block_main_field(blockColor, Moves, i + x, j);
		}
	}
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