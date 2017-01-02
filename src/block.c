#include "block.h"

#include "imageloader.h"
#include "renderer.h"
#include "window.h"

#include <stdlib.h>

BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];

static bool opportunity_create_block;

static bool check_create(int i0, int j0, int i1, int j1);

void init_main_field()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			mainField[i][j].color = BackgroundColor;
			mainField[i][j].status = Background;
		}
	}

	opportunity_create_block = true;
}

BlockArr (* get_main_field())[Y_MAIN_FIELD_SIZE]
{
	return mainField;
}

bool check_opportunity_create_block()
{
	return opportunity_create_block;
}

void recolor_main_field()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			draw_block_offset(mainField[i][j].color, (Point) { i * 32, j * 32 }, (Point) { X_MAIN_FIELD, Y_MAIN_FIELD });
		}
	}
}

void recolor_block_main_field(BlockColor blockColor, BlockStatus blockStatus, int i, int j)
{
	mainField[i][j].color = blockColor;
	mainField[i][j].status = blockStatus;

	draw_block_offset(blockColor, (Point) { i * 32, j * 32 }, (Point) { X_MAIN_FIELD, Y_MAIN_FIELD });
}

void generation_blocks(BlockColor blockColor, BlockType blockType)
{
	if (blockColor == RandomColor)
	{
		blockColor = rand() % NUMBER_OF_COLORS + 2;
	}

	switch (blockType)
	{
	case Square:
		create_square(blockColor, SQARE_SIZE, 4, 0);
		break;
	}
}

void create_square(BlockColor blockColor, int sqareSize, int i, int j)
{
	if ((0 <= i) && (i + sqareSize - 1 < X_MAIN_FIELD_SIZE) &&
		(0 <= j) && (j + sqareSize - 1 < Y_MAIN_FIELD_SIZE) &&
		check_create(i, j, i + sqareSize - 1, j + sqareSize - 1))
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

void moves_to_basis()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			if (mainField[i][j].status == Moves)
			{
				mainField[i][j].status = Basis;
			}
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
				opportunity_create_block = false;

				return false;
			}
		}
	}

	return true;
}