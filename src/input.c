#include "input.h"
#include "rotation.h"
#include "movement.h"

static void check_keycode(int keycode);

static KeyState keysHeld[MAX_KEYS];

void init_keys_state()
{
	for (int k = 0; k < MAX_KEYS; ++k)
	{
		keysHeld[k] = KeyUp;
	}
}

void unpress_keys()
{
	keysHeld[SDLK_w] = KeyUp;
	keysHeld[SDLK_UP] = KeyUp;

	/*keysHeld[SDLK_d] = KeyUp;
	keysHeld[SDLK_RIGHT] = KeyUp;*/

	keysHeld[SDLK_s] = KeyUp;
	keysHeld[SDLK_DOWN] = KeyUp;

	/*keysHeld[SDLK_a] = KeyUp;
	keysHeld[SDLK_LEFT] = KeyUp;*/
}

void handle_keydown(int keycode)
{
	check_keycode(keycode);

	switch (keysHeld[keycode])
	{
	case KeyUp:
		keysHeld[keycode] = KeyDown;
		break;
	case KeyDown:
		keysHeld[keycode] = KeyUsed;
		break;
	case KeyUsed:
		break;
	}
}

void handle_keyup(int keycode)
{
	check_keycode(keycode);

	keysHeld[keycode]= KeyUp;
}

KeyState key_held(int keycode)
{
	return  keysHeld[keycode];
}

KeyState check_key_movement_pressed()
{
	if (/*key_held(SDLK_w) == KeyDown || key_held(SDLK_UP) == KeyDown ||*/
		key_held(SDLK_d) == KeyDown || key_held(SDLK_RIGHT) == KeyDown ||
		key_held(SDLK_s) == KeyDown || key_held(SDLK_DOWN) == KeyDown ||
		key_held(SDLK_a) == KeyDown || key_held(SDLK_LEFT) == KeyDown)
	{
		return KeyDown;
	}

	return KeyUp;
}

static void check_keycode(int keycode)
{
	if (keycode >= MAX_KEYS)
	{
		printf("Keycode %d is out of range.\nForce quit.\n", keycode);
		exit(1);
	}
}

void key_tick()
{
	movement_dir_button();

	key_rotation();
}