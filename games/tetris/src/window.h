#pragma once

#include "SDL.h"

#include <stdbool.h>


/* ... */
bool init_window(const char* title, int width, int height);

/* ... */
void dispose_window(void);

/* ... */
SDL_Surface* get_screen(void);

/* заполнение экрана заданным цветом */
void clear_screen(int r, int g, int b, int a);

/* используется двойная буферизация. обменивает буферы */
void flip_screen(void);