#pragma once

#include "block.h"
#include "input.h"

#include <stdbool.h>

#define SIDES_SPEED 2

typedef enum
{
	Up,
	Right,
	Down,
	Left
} Direction;

typedef struct
{
	int u;
	int r;
	int d;
	int l;
} Move;

bool check_movement();

void move_toward(Direction direction);

void movement_dir_button();