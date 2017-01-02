#pragma once

#include "block.h"
#include "movement.h"

#include <stdbool.h>

bool* get_opportun_create_blocks();

void generation_blocks(enum BlockColor blockColor, enum BlockType blockType);

void create_square(enum BlockColor blockColor, int sqareSize, int i, int j);

void create_line(enum BlockColor blockColor, int i, int j);