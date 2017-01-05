#pragma once

#include "block.h"
#include "movement.h"

#include <stdbool.h>

bool* get_opportun_create_blocks();

bool generation_blocks(enum BlockColor blockColor, enum BlockType blockType, enum Direction direction);

bool check_create(int beginI, int beginJ, int endI, int endJ);

bool create_square(enum BlockColor blockColor, enum BlockStatus blockStatus, int sqareSize, int i, int j);

bool create_line(enum BlockColor blockColor, enum BlockStatus blockStatus, int i, int j, enum Direction direction);

bool create_j(enum BlockColor blockColor, enum BlockStatus blockStatus, int i, int j, enum Direction direction, enum BlockType blockType);

bool create_j_l(enum BlockColor blockColor, enum BlockStatus blockStatus, int i, int j, enum Direction direction);

bool create_j_r(enum BlockColor blockColor, enum BlockStatus blockStatus, int i, int j, enum Direction direction);

bool create_t(enum BlockColor blockColor, enum BlockStatus blockStatus, int i, int j, enum Direction direction);