#pragma once

#include "block.h"

void generation_random_block();

void random_color(enum BlockColor *blockColor);

void random_type(enum BlockType *blockType);

void random_direction(enum Direction *direction);

void init_generation_block();