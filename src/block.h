#pragma once

#include <stdbool.h>

#define X_MAIN_FIELD 12
#define Y_MAIN_FIELD 90

#define X_MAIN_FIELD_SIZE 10

#define Y_MAIN_FIELD_SIZE 20

#define SQARE_SIZE 2

#define NUMBER_OF_COLORS 4

typedef enum
{
	BackgroundImage,
	OtherImage
} BlockImage;

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
	Square,
	Line
} BlockType;


void init_main_field();

BlockArr (* get_main_field())[Y_MAIN_FIELD_SIZE];

bool check_opportunity_create_block();

void recolor_main_field();

void recolor_block_main_field(BlockColor blockColor, BlockStatus blockStatus, int i, int j);

void generation_blocks(BlockColor blockColor, BlockType blockType);

void create_square(BlockColor blockColor, int sqareSize, int i, int j);

void moves_to_basis();