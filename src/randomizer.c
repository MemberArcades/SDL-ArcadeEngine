#include "randomizer.h"

static BlockState nextBlock = { RandomType, RandomDirection, 0, 0, RandomColor };


static void randomized();


void generation_random_block()
{
	generation_blocks(nextBlock.color, nextBlock.type, nextBlock.direction);
	randomized();
};

static void randomized()
{
	random_color(&nextBlock.color);
	random_type(&nextBlock.type);
	random_direction(&nextBlock.direction);
}

void random_color(BlockColor *blockColor)
{
	*blockColor = rand() % NUMBER_OF_COLORS + 2;
}

void random_type(BlockType *blockType)
{
	*blockType = rand() % NUMBER_OF_TYPE + 1;
}

void random_direction(Direction *direction)
{
	*direction = rand() % NUMBER_OF_DIRECTION + 1;
}

void init_generation_block()
{
	generation_blocks(RandomColor, RandomType, RandomDirection);
	randomized();
}