#pragma once

#include "block.h"

typedef struct
{
	enum BlockType type;
	enum Direction direction;
	enum BlockColor color;
	int i;
	int j;
} BlockState;


BlockState* get_state_rotation();

void rotation();

void reboot_rotatoin_index(enum Direction direction);