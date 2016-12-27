#pragma once

#include "SDL.h"
#include <stdbool.h>

#define MAX_KEYS 323

void handle_keydown(int keycode);

void handle_keyup(int keycode);

/**
 * Проверяет, нажата ли заданная кнопка. 
 * \keycode: SDLK константа.
 */
bool key_held(int keycode);
