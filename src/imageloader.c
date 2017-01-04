#include "imageloader.h"

#define DIR_IMAGE "image/"

SDL_Surface *background;
SDL_Surface *blocks[2];
SDL_Surface *gaveOverImg;

SDL_Surface *load_image(char *filename)
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
	blocks[BackgroundImage] = load_image(DIR_IMAGE "tetris_block_background.png");
	blocks[OtherImage] = load_image(DIR_IMAGE "tetris_block_new.png");
	gaveOverImg = load_image(DIR_IMAGE "tetris_game_over.png");
}

void destroy_image()
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(blocks[BackgroundImage]);
	SDL_FreeSurface(blocks[OtherImage]);
	SDL_FreeSurface(gaveOverImg);
}

SDL_Surface* get_block_image(BlockImage block)
{
	return blocks[block];
}

SDL_Surface* get_background_image()
{
	return background;
}

SDL_Surface* get_game_over_image()
{
	return gaveOverImg;
}