#include "imageloader.h"

#include "block.h"
#include "fieldnextblock.h"


SDL_Surface *background;
SDL_Surface *blocks[NUMBER_OF_SKINS];
SDL_Surface *gaveOverImg;
SDL_Surface *symbolsImage;
SDL_Surface *menuBackgroundImage;
SDL_Surface *menuTextImage;

static int blockNumber = 0;


static SDL_Surface *load_image(char *filename);


static SDL_Surface *load_image(char *filename)
{
	SDL_Surface *inputImage = NULL;
	SDL_Surface *resultImage = NULL;

	inputImage = IMG_Load(filename);

	if (inputImage != NULL)
	{
		resultImage = SDL_DisplayFormatAlpha(inputImage);

		SDL_FreeSurface(inputImage);
	}
	else
	{
		printf("Error loading image %s\nForce quit.\n", filename);

		exit(1);
	}

	return resultImage;
}

void load_images()
{
	background = load_image(DIR_IMAGE  "tetris_background.png");
	blocks[0] = load_image(DIR_IMAGE "tetris_block_new.png");
	blocks[1] = load_image(DIR_IMAGE "tetris_block.png");
	gaveOverImg = load_image(DIR_IMAGE "tetris_game_over.png");
	symbolsImage = load_image(DIR_IMAGE "symbols.png");
	menuBackgroundImage = load_image(DIR_IMAGE "menu_background.png");
	menuTextImage = load_image(DIR_IMAGE "menu_text.png");
}

void destroy_image()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(gaveOverImg);
	SDL_FreeSurface(symbolsImage);
	SDL_FreeSurface(menuTextImage);
	SDL_FreeSurface(menuBackgroundImage);

	for (int i = 0; i < NUMBER_OF_SKINS; ++i)
	{
		SDL_FreeSurface(blocks[i]);
	}
}

SDL_Surface* get_block_image()
{
	return blocks[blockNumber];
}

SDL_Surface* get_background_image()
{
	return background;
}

SDL_Surface* get_game_over_image()
{
	return gaveOverImg;
}

SDL_Surface* get_symbols_image()
{
	return symbolsImage;
}

SDL_Surface* get_menu_background_image()
{
	return menuBackgroundImage;
}

SDL_Surface* get_menu_text_image()
{
	return menuTextImage;
}

void swap_block_texture()
{
	blockNumber = (blockNumber + 1) % NUMBER_OF_SKINS;

	recolor_main_field();
	draw_next_block();
}