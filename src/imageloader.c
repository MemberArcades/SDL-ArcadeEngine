#include "imageloader.h"

SDL_Surface *logo;

SDL_Surface *instruction;

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
	logo = load_image("images/logo.png");
	instruction = load_image("images/instruction.png");
}

void destroy_image()
{
	SDL_FreeSurface(logo);
	SDL_FreeSurface(instruction);
}

SDL_Surface* get_logo_image()
{
	return logo;
}

SDL_Surface* get_instruction_image()
{
	return instruction;
}