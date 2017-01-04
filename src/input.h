#pragma once

#include "SDL.h"
#include <stdbool.h>

#define MAX_KEYS 323

typedef enum
{
	KeyUp,
	KeyDown,
	KeyUsed
} KeyState;

void init_keys_state();

void unpress_keys();

/* Обработчик нажатия кнопки */
void handle_keydown(int keycode);

/* Обработчик отпуская кнопки */
void handle_keyup(int keycode);

/* Проверяет, нажата ли заданная кнопка. */
KeyState key_held(int keycode);

KeyState check_key_movement_pressed();