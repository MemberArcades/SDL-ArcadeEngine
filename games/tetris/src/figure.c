#include "figure.h"

#include "randomizer.h"
#include "rotation.h"
#include "block.h"


static bool opportunityCreateBlock;


static bool create_n(enum BlockColor blockColor, enum BlockStatus blockStatus, int i, int j, enum Direction direction, enum BlockType blockType);


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
		if (!create_square(blockColor, Moves, SQARE_SIZE, 4, 0))
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

		if (!create_line(blockColor, Moves, i, 0, direction))
		{
			opportunityCreateBlock = false;

			return false;
		}

		get_state_rotation()->i = i;
		get_state_rotation()->j = 0;

		break;
	}
	case JL:
	case JR:
	case T:
	case NL:
	case NR:
		if (!create_jt(blockColor, Moves, 4, 0, direction, blockType))
		{
			opportunityCreateBlock = false;

			return false;
		}

		get_state_rotation()->i = 4;
		get_state_rotation()->j = 0;

		break;
	}

	return true;
}

bool check_create(int beginI, int beginJ, int endI, int endJ)
{
	if ((0 > beginI) || (endI >= X_MAIN_FIELD_SIZE) ||
		(0 > beginJ) || (endJ >= Y_MAIN_FIELD_SIZE))
	{
		return false;
	}

	for (int i = beginI; i <= endI; ++i)
	{
		for (int j = beginJ; j <= endJ; ++j)
		{
			if (get_main_field()[i][j].status == Basis)
			{
				return false;
			}
		}
	}

	return true;
}

bool create_square(BlockColor blockColor, BlockStatus blockStatus, int sqareSize, int i, int j)
{
	if (check_create(i, j, i + sqareSize - 1, j + sqareSize - 1))
	{
		for (int x = 0; x < sqareSize; ++x)
		{
			for (int y = 0; y < sqareSize; ++y)
			{
				recolor_block_main_field(blockColor, blockStatus, i + x, j + y);
			}
		}

		return true;
	}

	return false;
}

bool create_line(BlockColor blockColor, BlockStatus blockStatus, int i, int j, Direction direction)
{
	switch (direction)
	{
	case Up:
	case Down:
		if (check_create(i, j, i + 3, j))
		{
			for (int x = 0; x < 4; ++x)
			{
				recolor_block_main_field(blockColor, blockStatus, i + x, j);
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
				recolor_block_main_field(blockColor, blockStatus, i, j + y);
			}

			return true;
		}

		break;
	}

	return false;
}

bool create_jt(BlockColor blockColor, BlockStatus blockStatus, int i, int j, Direction direction, BlockType blockType)
{
	if (blockType == NL || blockType == NR)
	{
		if (create_n(blockColor, blockStatus, i, j, direction, blockType))
		{
			return true;
		}
	}
	else
	{
		switch (direction)
		{
		case Up:
			if (check_create(i, j, i + 2, j + 1))
			{
				switch (blockType)
				{
				case JL:
					recolor_block_main_field(blockColor, blockStatus, i, j);
					break;
				case T:
					recolor_block_main_field(blockColor, blockStatus, i + 1, j);
					break;
				case JR:
					recolor_block_main_field(blockColor, blockStatus, i + 2, j);
					break;
				}

				for (int x = 0; x < 3; ++x)
				{
					recolor_block_main_field(blockColor, blockStatus, i + x, j + 1);
				}

				return true;
			}

			break;
		case Down:
			if (check_create(i, j, i + 2, j + 1))
			{
				switch (blockType)
				{
				case JL:
					recolor_block_main_field(blockColor, blockStatus, i + 2, j + 1);
					break;
				case T:
					recolor_block_main_field(blockColor, blockStatus, i + 1, j + 1);
					break;
				case JR:
					recolor_block_main_field(blockColor, blockStatus, i, j + 1);
					break;
				}

				for (int x = 0; x < 3; ++x)
				{
					recolor_block_main_field(blockColor, blockStatus, i + x, j);
				}

				return true;
			}

			break;
		case Right:
			if (check_create(i, j, i + 1, j + 2))
			{
				switch (blockType)
				{
				case JL:
					recolor_block_main_field(blockColor, blockStatus, i + 1, j);
					break;
				case T:
					recolor_block_main_field(blockColor, blockStatus, i + 1, j + 1);
					break;
				case JR:
					recolor_block_main_field(blockColor, blockStatus, i + 1, j + 2);
					break;
				}

				for (int y = 0; y < 3; ++y)
				{
					recolor_block_main_field(blockColor, blockStatus, i, j + y);
				}

				return true;
			}
		case Left:
			if (check_create(i, j, i + 1, j + 2))
			{
				switch (blockType)
				{
				case JL:
					recolor_block_main_field(blockColor, blockStatus, i, j + 2);
					break;
				case T:
					recolor_block_main_field(blockColor, blockStatus, i, j + 1);
					break;
				case JR:
					recolor_block_main_field(blockColor, blockStatus, i, j);
					break;
				}

				for (int y = 0; y < 3; ++y)
				{
					recolor_block_main_field(blockColor, blockStatus, i + 1, j + y);
				}


				return true;
			}

			break;
		}
	}

	return false;
}

static bool create_n(BlockColor blockColor, BlockStatus blockStatus, int i, int j, Direction direction, BlockType blockType)
{
	switch (direction)
	{
	case Up:
	case Down:
		if (check_create(i, j, i + 2, j + 1))
		{
			for (int k = 0; k < 2; ++k)
			{
				recolor_block_main_field(blockColor, blockStatus, i + 1, j + k);
			}

			if (blockType == NL)
			{
				recolor_block_main_field(blockColor, blockStatus, i, j + 1);
				recolor_block_main_field(blockColor, blockStatus, i + 2, j);
			}
			else
			{
				recolor_block_main_field(blockColor, blockStatus, i, j);
				recolor_block_main_field(blockColor, blockStatus, i + 2, j + 1);
			}

			return true;
		}

		break;
	case Right:
	case Left:
		if (check_create(i, j, i + 1, j + 2))
		{
			for (int k = 0; k < 2; ++k)
			{
				recolor_block_main_field(blockColor, blockStatus, i + k, j + 1);
			}

			if (blockType == NL)
			{
				recolor_block_main_field(blockColor, blockStatus, i, j);
				recolor_block_main_field(blockColor, blockStatus, i + 1, j + 2);
			}
			else
			{
				recolor_block_main_field(blockColor, blockStatus, i, j + 2);
				recolor_block_main_field(blockColor, blockStatus, i + 1, j);
			}

			return true;
		}

		break;
	}

	return false;
}