#include "randomizer.h"
#include "fieldnextblock.h"
#include "block.h"

static NextBlock nextBlock;


static void randomized();


void generation_random_block()
{
	if (generation_blocks(nextBlock.color, nextBlock.type, nextBlock.direction))
	{
		randomized();
		draw_next_block();
	}
};

static void randomized()
{
	random_color(&nextBlock.color);
	random_type(&nextBlock.type);
	random_direction(&nextBlock.direction);
}

void random_color(enum BlockColor *blockColor)
{
	*blockColor = rand() % NUMBER_OF_COLORS + 2;
}

void random_type(enum BlockType *blockType)
{
	*blockType = rand() % NUMBER_OF_TYPE + 1;
}

void random_direction(enum Direction *direction)
{
	*direction = rand() % NUMBER_OF_DIRECTION + 1;
}

void init_generation_block()
{
	generation_blocks(RandomColor, RandomType, RandomDirection);
	randomized();
	draw_next_block();
}

NextBlock* get_next_block()
{
	return &nextBlock;
}