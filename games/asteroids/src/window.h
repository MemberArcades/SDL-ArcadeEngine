#pragma once

#include <stdbool.h>

#include "SDL.h"

/* ... */
bool init_window(const char* title, int width, int height);

/* ... */
void dispose_window(void);

/* ... */
SDL_Surface *get_screen(void);

/* заполнение экрана заданным цветом */
void clear_screen(int r, int g, int b, int a);

/* ... */
void apply_surface(int x, int y, SDL_Surface* source);

/* используется двойная буферизация. обменивает буферы */
void flip_screen(void);
