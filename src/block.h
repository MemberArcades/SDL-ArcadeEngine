#pragma once

#define X_MAIN_FIELD 12
#define Y_MAIN_FIELD 90

#define X_MAIN_FIELD_SIZE 10
#define Y_MAIN_FIELD_SIZE 20

typedef enum
{
	BackgroundImage,
	OtherImage
} BlockImage;

typedef enum
{
	BackgroundColor,
	RedColor,
	BlueColor,
	GreenColor,
	PurpleColor
} BlockColor;

typedef enum
{
	Normal,
	Restructure,
	Moves
} BlockStatus;

typedef struct
{
	BlockColor color;
	BlockStatus status;
} BlockArr;

void init_main_field();

void restructure_main_field();

void recolor_block_main_field(BlockColor blockColor, int i, int j);