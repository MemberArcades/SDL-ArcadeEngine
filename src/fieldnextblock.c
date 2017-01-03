#include "fieldnextblock.h"
#include "renderer.h"
#include "randomizer.h"

static void cleaned_field();

static void draw_sqare();

static void draw_line(enum Direction direction);


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

static void draw_line(enum Direction direction)
{
	switch (direction)
	{
	case Up:
	case Down:
		for (int i = 0; i < X_FIELD_NEXT_BLOCK_SIZE; ++i)
		{
			for (int j = 4; j < Y_FIELD_NEXT_BLOCK_SIZE; ++j)
			{
				draw_block_offset(get_next_block()->color, (Point) { i * 32, j * 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			}
		}

		break;
	case Right:
	case Left:
		for (int i = 2; i < 3; ++i)
		{
			for (int j = 0; j < Y_FIELD_NEXT_BLOCK_SIZE; ++j)
			{
				draw_block_offset(get_next_block()->color, (Point) { i * 32, j * 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			}
		}

		break;
	}
}