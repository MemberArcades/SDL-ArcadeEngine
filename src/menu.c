#include "menu.h"

#include <stdbool.h>

#include "input.h"
#include "main.h"
#include "renderer.h"
#include "window.h"

static void draw_info_screen(void);

static void process_enemies(MenuSystem *menuSystem);

void menu_init(MenuSystem *menuSystem)
{
	menuSystem->action = Nothing;
	menuSystem->ticksSinceModeChange = SDL_GetTicks();

	enemies_init(&menuSystem->enemy, ENEMIES);
}

void menu_tick(MenuSystem *menuSystem)
{
	bool startNew = key_held(SDLK_KP_ENTER) || key_held(SDLK_RETURN);

	if (startNew)
	{
		menuSystem->action = GoToGame;
	}

	process_enemies(menuSystem);
}

void menu_render(MenuSystem *menuSystem)
{
	draw_info_screen();

	for (int i = 0; i < MAX_ENEMIES; ++i)
		draw_enemy(get_screen(), menuSystem->enemy[i]);

}

static void draw_info_screen(void)
{
	draw_logo();
	draw_instruction();
}

static void process_enemies(MenuSystem *menuSystem)
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		Enemy *enemy = &menuSystem->enemy[i];

		if (!enemy->alive)
			continue;

		Vector temp = enemy->body.direction;
		mul_vector(&temp, enemy->body.velocity);

		add_vector(&enemy->body.position, temp);

		inf_screen(&enemy->body);

	}
}