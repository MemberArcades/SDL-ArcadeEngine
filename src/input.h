#pragma once

#include "SDL.h"
#include <stdbool.h>
#include "main.h"
#include "menu.h"

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

bool check_key_down_pressed();

void key_tick(int key, enum ProgramState *state);

bool* get_key_flag();

bool pushed_enter(int key);

bool pushed_up(int key);

bool pushed_down(int key);

bool pushed_right(int key);

bool pushed_left(int key);