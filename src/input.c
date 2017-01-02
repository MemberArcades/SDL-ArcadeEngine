#include "input.h"

static void check_keycode(int keycode);

static bool keysHeld[MAX_KEYS] = { false };

void handle_keydown(int keycode)
{
	check_keycode(keycode);
	keysHeld[keycode] = true;
}

void handle_keyup(int keycode)
{
	check_keycode(keycode);
	keysHeld[keycode] = false;
}

bool key_held(int keycode)
{
	return  keysHeld[keycode];
}

bool check_key_movement_pressed()
{
	if (key_held(SDLK_w) || key_held(SDLK_UP) ||
		key_held(SDLK_d) || key_held(SDLK_RIGHT) ||
		key_held(SDLK_s) || key_held(SDLK_DOWN) ||
		key_held(SDLK_a) || key_held(SDLK_LEFT))
	{
		return true;
	}

	return false;
}

static void check_keycode(int keycode)
{
	if (keycode >= MAX_KEYS)
	{
		printf("Keycode %d is out of range.\nForce quit.\n", keycode);
		exit(1);
	}
}