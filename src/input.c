#include "input.h"

static bool keysHeld[MAX_KEYS] = { false };

void handle_keydown(int keycode)
{
	keysHeld[keycode] = true;
}

void handle_keyup(int keycode)
{
	keysHeld[keycode] = false;
}

bool key_held(int keycode)
{
	return  keysHeld[keycode];
}
