#include "fieldnextblock.h"
#include "renderer.h"
#include "randomizer.h"

static void cleaned_field();

static void draw_sqare();

static void draw_line(Direction direction);

static void draw_j(Direction direction, BlockType type);


void draw_next_block()
{
	cleaned_field();

	switch (get_next_block()->type)
	{
	case Square:
		draw_sqare();
		break;
	case Line:
		draw_line(get_next_block()->direction);
		break;
	case JL:
	case JR:
		draw_j(get_next_block()->direction, get_next_block()->type);
		break;
	}
}

static void cleaned_field()
{
	for (int i = 0; i < X_FIELD_NEXT_BLOCK_SIZE; ++i)
	{
		for (int j = 0; j < Y_FIELD_NEXT_BLOCK_SIZE; ++j)
		{
			draw_block_offset(BackgroundColor, (Point) { i * 32, j * 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}
	}
}

static void draw_sqare()
{
	for (int i = 0; i < SQARE_SIZE; ++i)
	{
		for (int j = 0; j < SQARE_SIZE; ++j)
		{
			draw_block_offset(get_next_block()->color, (Point) { i * 32, j * 32 }, (Point) { X_SQARE_OFFSET, Y_SQARE_OFFSET });
		}
	}
}

static void draw_line(Direction direction)
{
	switch (direction)
	{
	case Up:
	case Down:
		for (int i = 0; i < X_FIELD_NEXT_BLOCK_SIZE  - 1; ++i)
		{
			for (int j = 4; j < Y_FIELD_NEXT_BLOCK_SIZE; ++j)
			{
				draw_block_offset(get_next_block()->color, (Point) { i * 32 + 16, j * 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			}
		}

		break;
	case Right:
	case Left:
			for (int j = 1; j < Y_FIELD_NEXT_BLOCK_SIZE; ++j)
			{
				draw_block_offset(get_next_block()->color, (Point) { 64 , j * 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			}

		break;
	}
}

static void draw_j(Direction direction, BlockType type)
{
	switch (direction)
	{
	case Up:
		for (int i = 1; i < 4; ++i)
		{
				draw_block_offset(get_next_block()->color, (Point) { i * 32, 128 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		if (type == JL)
		{
			draw_block_offset(get_next_block()->color, (Point) { 32, 96 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}
		else
		{
			draw_block_offset(get_next_block()->color, (Point) { 96, 96 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		break;
	case Right:
	case Left:
		for (int j = 2; j < Y_FIELD_NEXT_BLOCK_SIZE; ++j)
		{
			draw_block_offset(get_next_block()->color, (Point) { 64, j * 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		int i, j;

		if (direction == Right)
		{
			i = 3;

			if (type == JR)
			{
				j = 4;
			}
			else
			{
				j = 2;
			}
		}
		else
		{
			i = 1;

			if (type == JR)
			{
				j = 2;
			}
			else
			{
				j = 4;
			}
		}

		draw_block_offset(get_next_block()->color, (Point) { i * 32, j * 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });

		break;
	case Down:
		for (int i = 1; i < 4; ++i)
		{
			draw_block_offset(get_next_block()->color, (Point) { i * 32, 96 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		if (type == JR)
		{
			draw_block_offset(get_next_block()->color, (Point) { 32, 128 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}
		else
		{
			draw_block_offset(get_next_block()->color, (Point) { 96, 128 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		break;
	}
}