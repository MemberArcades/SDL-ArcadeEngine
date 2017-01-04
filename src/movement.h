#pragma once

#include "block.h"
#include "input.h"

#include <stdbool.h>

#define SIDES_SPEED 2
#define DOWN_SPEED 30
#define MAX_SPEED 6

#define BOOST 3000

typedef enum
{
	RandomDirection,
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

int* get_sum_boost();

bool check_movement();

bool check_move(Direction direction);

void move_down();

void move_toward(Direction direction);

void movement_dir_button();

void blocks_to_moves(int j);