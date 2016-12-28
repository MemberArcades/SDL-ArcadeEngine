#pragma once

#include <SDL.h>
#include <SDL_image.h>

SDL_Surface *load_file_image(char *filename);

/* filename - это путь до изображения
   x, y - это координаты точки, куда вставляется изображение
   iM может равняться NULL, тогда выводится изображение целиком, 
   при наличии iM выводится та часть изображения, которая
   соответствует заданным параметрам*/
void load_image(char *filename, int x, int y, SDL_Rect *iM, SDL_Surface* screen);
