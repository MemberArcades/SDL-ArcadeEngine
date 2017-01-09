#include "input.h"
#include "rotation.h"
#include "movement.h"
#include "menu.h"
#include "main.h"

static void check_keycode(int keycode);

static KeyState keysHeld[MAX_KEYS];

bool pauseFlag = false;

void init_keys_state()
{
	for (int k = 0; k < MAX_KEYS; ++k)
	{
		keysHeld[k] = KeyUp;
	}
}

void unpress_keys()
{
	keysHeld[SDLK_s] = KeyUp;
	keysHeld[SDLK_DOWN] = KeyUp;
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

bool check_key_down_pressed()
{
	if (keysHeld[SDLK_s] || keysHeld[SDLK_DOWN])		
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

void key_tick(int key, ProgramState *state)
{
	if (*state == Play)
	{
		movement_dir_button(key);

		if (SDLK_SPACE == key)
		{
			if (!pauseFlag)
			{
				rotation();
			}
			else
			{
				pauseFlag = false;
			}
		}
	}
}

bool* get_key_flag()
{
	return &pauseFlag;
}

bool pushed_enter(int key)
{
	if (key == SDLK_RETURN || key == SDLK_SPACE)
	{
		return true;
	}

	return false;
}

bool pushed_up(int key)
{
	if (key == SDLK_UP || key == SDLK_w)
	{
		return true;
	}

	return false;
}

bool pushed_down(int key)
{
	if (key == SDLK_DOWN || key == SDLK_s)
	{
		return true;
	}

	return false;
}

bool pushed_right(int key)
{
	if (key == SDLK_RIGHT || key == SDLK_d)
	{
		return true;
	}

	return false;
}

bool pushed_left(int key)
{
	if (key == SDLK_LEFT || key == SDLK_a)
	{
		return true;
	}

	return false;
}