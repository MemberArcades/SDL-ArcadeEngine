#include "picture.h"

SDL_Texture* loadTexture(char *file, SDL_Renderer *renderer)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, file);

	return texture;
}
