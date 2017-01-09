#pragma once

#include <stdbool.h>

#include "movement.h"
#include "figure.h"
#include "rotation.h"
#include "game.h"
#include "randomizer.h"

#define X_MAIN_FIELD 12
#define Y_MAIN_FIELD 90

#define X_MAIN_FIELD_SIZE 10
#define Y_MAIN_FIELD_SIZE 20

#define SQARE_SIZE 2

#define NUMBER_OF_COLORS 4
#define NUMBER_OF_TYPE 7
#define NUMBER_OF_DIRECTION 4


typedef enum
{
	BackgroundColor,
	RandomColor,
	RedColor,
	BlueColor,
	GreenColor,
	PurpleColor,
} BlockColor;

typedef enum
{
	Background,
	Basis,
	Restructure,
	Moves
} BlockStatus;

typedef struct
{
	BlockColor color;
	BlockStatus status;
} BlockArr;

typedef enum
{
	RandomType,
	Square,
	Line,
	JL,
	JR,
	T,
	NL,
	NR
} BlockType;


void init_main_field();

BlockArr (* get_main_field())[Y_MAIN_FIELD_SIZE];

void recolor_main_field();

void recolor_block_main_field(BlockColor blockColor, BlockStatus blockStatus, int i, int j);

void moves_to_basis();

void destroy_full_line();

void blocks_to_moves(int j);