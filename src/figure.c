#include "figure.h"
#include "randomizer.h"
#include "rotation.h"

extern BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];

static bool opportunityCreateBlock;


static bool check_create(int i0, int j0, int i1, int j1);


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
			opportunityCreateBlock = false;

			return false;
		}

		get_state_rotation()->i = 4;
		get_state_rotation()->j = 0;

		break;
	case Line:
	{
		int i = 3;

		if ((direction == Right) || (direction == Left))
		{
			++i;
		}

		if (!create_line(blockColor, i, 0, direction))
		{
			opportunityCreateBlock = false;

			return false;
		}

		get_state_rotation()->i = i;
		get_state_rotation()->j = 0;

		break;
	}
	case JL:
		if (!create_j_l(blockColor, 4, 0, direction))
		{
			opportunityCreateBlock = false;

			return false;
		}

		get_state_rotation()->i = 4;
		get_state_rotation()->j = 0;

		break;
	case JR:
	{		
		int i = 4;
		
		if (direction == Up)
		{
			i = 6;
		}
		if (!create_j_r(blockColor, i, 0, direction))
		{
			opportunityCreateBlock = false;

			return false;
		}

		get_state_rotation()->i = i;
		get_state_rotation()->j = 0;

		break;
	}
	}

	return true;
}

static bool check_create(int i0, int j0, int i1, int j1)
{
	if ((0 > i0) || (i1 >= X_MAIN_FIELD_SIZE) ||
		(0 > j0) || (j1 >= Y_MAIN_FIELD_SIZE))
	{
		return false;
	}

	for (i0; i0 <= i1; ++i0)
	{
		for (j0; j0 <= j1; ++j0)
		{
			if (mainField[i0][j0].status != Background && mainField[i0][j0].status != Moves)
			{

				return false;
			}
		}
	}

	return true;
}

bool create_square(BlockColor blockColor, int sqareSize, int i, int j)
{
	if (check_create(i, j, i + sqareSize - 1, j + sqareSize - 1))
	{
		for (int x = 0; x < sqareSize; ++x)
		{
			for (int y = 0; y < sqareSize; ++y)
			{
				recolor_block_main_field(blockColor, Moves, i + x, j + y);
			}
		}

		return true;
	}

	return false;
}

bool create_line(BlockColor blockColor, int i, int j, Direction direction)
{
	switch (direction)
	{
	case Up:
	case Down:
		if (check_create(i, j, i + 3, j))
		{
			for (int x = 0; x < 4; ++x)
			{
				recolor_block_main_field(blockColor, Moves, i + x, j);
			}

			return true;
		}

		break;
	case Right:
	case Left:
		if (check_create(i, j, i, j + 3))
		{
			for (int y = 0; y < 4; ++y)
			{
				recolor_block_main_field(blockColor, Moves, i, j + y);
			}

			return true;
		}

		break;
	}

	return false;
}

bool create_j_l(enum BlockColor blockColor, int i, int j, enum Direction direction)
{
	switch (direction)
	{
	case Up:
	case Down:
		if (check_create(i, j, i + 2, j + 1))
		{
			if (direction == Up)
			{
				recolor_block_main_field(blockColor, Moves, i, j);

				for (int x = 0; x < 3; ++x)
				{
					recolor_block_main_field(blockColor, Moves, i + x, j + 1);
				}
			}
			else
			{
				recolor_block_main_field(blockColor, Moves, i + 2, j + 1);

				for (int x = 0; x < 3; ++x)
				{
					recolor_block_main_field(blockColor, Moves, i + x, j);
				}
			}

			return true;
		}

		break;
	case Right:
		if (check_create(i, j, i + 1, j + 2))
		{
			recolor_block_main_field(blockColor, Moves, i + 1, j);

			for (int y = 0; y < 3; ++y)
			{
				recolor_block_main_field(blockColor, Moves, i, j + y);
			}

			return true;
		}
	case Left:
		if (check_create(i, j, i + 1, j + 2))
		{
			recolor_block_main_field(blockColor, Moves, i, j + 2);

			for (int y = 0; y < 3; ++y)
			{
				recolor_block_main_field(blockColor, Moves, i + 1, j + y);
			}


			return true;
		}

		break;
	}

	return false;
}

bool create_j_r(enum BlockColor blockColor, int i, int j, enum Direction direction)
{
	switch (direction)
	{
	case Up:
		if (check_create(i, j, i + 2, j + 1))
		{
			recolor_block_main_field(blockColor, Moves, i + 2, j);

			for (int x = 0; x < 3; ++x)
			{
				recolor_block_main_field(blockColor, Moves, i + x, j + 1);
			}
			
			return true;
		}

		break;
	case Down:
		if (check_create(i, j, i + 2, j + 1))
		{
			recolor_block_main_field(blockColor, Moves, i, j + 1);

			for (int x = 0; x < 3; ++x)
			{
				recolor_block_main_field(blockColor, Moves, i + x, j);
			}

			return true;
		}

		break;
	case Right:
		
		if (check_create(i, j, i + 1, j + 2))
		{
			recolor_block_main_field(blockColor, Moves, i + 1, j + 2);

			for (int y = 0; y < 3; ++y)
			{
				recolor_block_main_field(blockColor, Moves, i, j + y);
			}

			return true;
		}
	case Left:
		if (check_create(i, j, i + 1, j + 2))
		{
			recolor_block_main_field(blockColor, Moves, i, j);

			for (int y = 0; y < 3; ++y)
			{
				recolor_block_main_field(blockColor, Moves, i + 1, j + y);
			}

			return true;
		}

		break;
	}

	return false;
}