#include "imageloader.h"

SDL_Surface *load_file_image(char *filename)
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

void load_image(char *filename, int x, int y, SDL_Rect *iM, SDL_Surface* screen)
{
	SDL_Surface *image = NULL;

	if ((image = load_file_image(filename)) == NULL)
	{
		printf("Error loading image %s\nForce quit.\n", filename);

		exit(1);
	}

	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	if (iM == NULL)
	{
		SDL_BlitSurface(image, NULL, screen, &offset);
	}
	else
	{
		SDL_BlitSurface(image, iM, screen, &offset);
	}

	SDL_FreeSurface(image);
}
