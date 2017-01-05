#include "imageloader.h"


SDL_Surface *background;
SDL_Surface *blocks[NUMBER_OF_SKINS];
SDL_Surface *gaveOverImg;
SDL_Surface *numbersImage;


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
	numbersImage = load_image(DIR_IMAGE "numbers.png");
}

void destroy_image()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(gaveOverImg);
	SDL_FreeSurface(numbersImage);

	for (int i = 0; i < NUMBER_OF_SKINS; ++i)
	{
		SDL_FreeSurface(blocks[i]);
	}
}

SDL_Surface* get_block_image()
{
	return blocks[0];
}

SDL_Surface* get_background_image()
{
	return background;
}

SDL_Surface* get_game_over_image()
{
	return gaveOverImg;
}

SDL_Surface* get_numbers_image()
{
	return numbersImage;
}