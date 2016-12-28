#pragma once

#include <stdbool.h>
#include "SDL.h"
#include "imageloader.h"

void draw_point(SDL_Surface *surface, int x, int y, Uint32 color);

void draw_line(SDL_Surface *surface, int x0, int y0, int x1, int y1, Uint32 color);

/*filename - это путь до изображения
x, y - это координаты точки, куда вставляется изображение
iM может равняться NULL, тогда выводится изображение целиком,
при наличии iM выводится та часть изображения, которая
соответствует заданным параметрам*/
void draw_image(char *filename, int x, int y, SDL_Rect *iM, SDL_Surface* screen);
