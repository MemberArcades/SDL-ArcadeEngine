#pragma once

#include "block.h"

typedef struct
{
	enum BlockType type;
	enum Direction direction;
	int i;
	int j;
	enum BlockColor color;
} BlockState;


BlockState* get_state_rotation();

void key_rotation();

void reboot_rotatoin_index(enum Direction direction);