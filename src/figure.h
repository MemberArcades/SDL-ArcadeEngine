#pragma once

#include "block.h"
#include "movement.h"

#include <stdbool.h>

bool* get_opportun_create_blocks();

bool check_create(int i0, int j0, int i1, int j1);

bool generation_blocks(enum BlockColor blockColor, enum BlockType blockType, enum Direction direction);

bool create_square(enum BlockColor blockColor, enum BlockType blockType, int sqareSize, int i, int j);

bool create_line(enum BlockColor blockColor, enum BlockType blockType, int i, int j, enum Direction direction);

bool create_j_l(enum BlockColor blockColor, enum BlockType blockType, int i, int j, enum Direction direction);

bool create_j_r(enum BlockColor blockColor, enum BlockType blockType, int i, int j, enum Direction direction);