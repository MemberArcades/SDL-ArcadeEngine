#pragma once

#include "block.h"

typedef struct
{
	enum BlockType type;
	enum BlockColor color;
	enum Direction direction;
} NextBlock;

void generation_random_block();

void random_color(enum BlockColor *blockColor);

void random_type(enum BlockType *blockType);

void random_direction(enum Direction *direction);

void init_generation_block();

NextBlock* get_next_block();