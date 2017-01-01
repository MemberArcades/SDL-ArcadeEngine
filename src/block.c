#include "block.h"

#include "imageloader.h"
#include "renderer.h"
#include "window.h"

static BlockArr mainField[X_MAIN_FIELD_SIZE][Y_MAIN_FIELD_SIZE];

void init_main_field()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			mainField[i][j].color = BackgroundColor;
			mainField[i][j].status = Normal;
		}
}

void restructure_main_field()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			if (mainField[i][j].status == Restructure)
				draw_block_offset(mainField[i][j].color, (Point) { i * 32, j * 32 }, (Point) { X_MAIN_FIELD, Y_MAIN_FIELD });
		}
}

void recolor_block_main_field(BlockColor blockColor, int i, int j)
{
	mainField[i][j].color = blockColor;
	mainField[i][j].status = Restructure;
}