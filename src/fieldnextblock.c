#include "fieldnextblock.h"

#include "renderer.h"
#include "randomizer.h"
#include "figure.h"
#include "movement.h"


static void cleaned_field();

static void draw_sqare();

static void draw_line(enum Direction direction);

static void draw_jt(enum Direction direction, enum BlockType type);

static void draw_n(enum Direction direction, enum BlockType type);


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
	case T:
		draw_jt(get_next_block()->direction, get_next_block()->type);
		break;
	case NL:
	case NR:
		draw_n(get_next_block()->direction, get_next_block()->type);
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
			draw_block_offset(get_next_block()->color, (Point) { i * 32 + 16, 64 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		break;
	case Right:
	case Left:
			for (int j = 1; j < Y_FIELD_NEXT_BLOCK_SIZE; ++j)
			{
				draw_block_offset(get_next_block()->color, (Point) { 64 , j * 32 - 16 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			}

		break;
	}
}

static void draw_jt(Direction direction, BlockType type)
{
	switch (direction)
	{
	case Up:
		for (int i = 1; i < 4; ++i)
		{
			draw_block_offset(get_next_block()->color, (Point) { i * 32, 80 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		switch (type)
		{
		case JL:
			draw_block_offset(get_next_block()->color, (Point) { 32, 48 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			
			break;
		case JR:
			draw_block_offset(get_next_block()->color, (Point) { 96, 48 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });

			break;
		case T:
			draw_block_offset(get_next_block()->color, (Point) { 64, 48 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });

			break;
		}

		break;
	case Right:
	case Left:
	{
		int i, j, rot;

		if (direction == Right)
		{
			i = 3;
			rot = -16;

			switch (type)
			{
			case JL:
				j = 2;

				break;
			case JR:
				j = 4;

				break;
			case T:
				j = 3;

				break;
			}
		}
		else
		{
			i = 1;
			rot = 16;

			switch (type)
			{
			case JL:
				j = 4;

				break;
			case JR:
				j = 2;

				break;
			case T:
				j = 3;

				break;
			}
		}

		for (int j = 1; j < Y_FIELD_NEXT_BLOCK_SIZE - 1; ++j)
		{
			draw_block_offset(get_next_block()->color, (Point) { 64 + rot, j * 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		draw_block_offset(get_next_block()->color, (Point) { i * 32 + rot, j * 32 - 32}, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });

		break;
	}
	case Down:
		for (int i = 1; i < 4; ++i)
		{
			draw_block_offset(get_next_block()->color, (Point) { i * 32, 48 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		switch (type)
		{
		case JL:
			draw_block_offset(get_next_block()->color, (Point) { 96, 80 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });

			break;
		case JR:
			draw_block_offset(get_next_block()->color, (Point) { 32, 80 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });

			break;
		case T:
			draw_block_offset(get_next_block()->color, (Point) { 64, 80 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });

			break;
		}

		break;
	}
}

static void draw_n(Direction direction, BlockType type)
{
	switch (direction)
	{
	case Up:
	case Down:
		for (int j = 1; j < 3; ++j)
		{
			draw_block_offset(get_next_block()->color, (Point) { 64, 32 * j + 16 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		if (type == NL)
		{
			draw_block_offset(get_next_block()->color, (Point) { 96, 48 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			draw_block_offset(get_next_block()->color, (Point) { 32, 80 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}
		else
		{
			draw_block_offset(get_next_block()->color, (Point) { 32, 48 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			draw_block_offset(get_next_block()->color, (Point) { 96, 80 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		break;
	case Right:
	case Left:
		for (int i = 1; i < 3; ++i)
		{
			draw_block_offset(get_next_block()->color, (Point) { 32 * i + 16, 64 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		if (type == NL)
		{
			draw_block_offset(get_next_block()->color, (Point) { 48, 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			draw_block_offset(get_next_block()->color, (Point) { 80, 96 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}
		else
		{
			draw_block_offset(get_next_block()->color, (Point) { 48, 96 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
			draw_block_offset(get_next_block()->color, (Point) { 80, 32 }, (Point) { X_FIELD_NEXT_BLOCK, Y_FIELD_NEXT_BLOCK });
		}

		break;
	}
}