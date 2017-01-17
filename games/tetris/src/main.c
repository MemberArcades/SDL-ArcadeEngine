#include "main.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_gfxPrimitives.h"

#include "window.h"
#include "renderer.h"
#include "imageloader.h"
#include "fpsmanager.h"
#include "input.h"
#include "game.h"
#include "gamescore.h"
#include "music.h"
#include "menu.h"

#include <stdbool.h>


static ProgramState state = Menu;

static Game game;

static bool gameRunning = true;


/* Иницализация всех ресурсов */
static void resource_init(void);

/* Освобождение выделенной памяти */
static void clean_up(void);

/* Основой цикл игры */
static void main_loop(void);

/* Вся игровая логика */
static void internal_tick(void);

/* Вся графика */
static void internal_render(void);

/* Обработка ввода */
static void process_events(void);


int main(int argc, char* args[])
{
	resource_init();

	game_init(&game);

	main_loop();

	clean_up();

	return 0;
}

static void main_loop(void)
{
	while (gameRunning)
	{
		process_events();

		internal_tick();

		internal_render();

		fps_sleep();
	}
}

static void internal_tick(void) 
{
	switch (state)
	{
	case Play:
		game_tick(&game);

		if (game_over(&game))
		{
			state = End;
		}

		break;
	case End:
		if (key_held(SDLK_RETURN))
		{
			game_init(&game);
			state = Play;
		}

		break;
	case Out:
		gameRunning = false;

		break;
	}
}

static void internal_render(void)
{
	if (state == Menu || state == Pause)
	{
		draw_menu();
	}

	flip_screen();
}

static void process_events(void)
{
	static SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;

			break;
		case SDL_KEYDOWN:
			key_tick(event.key.keysym.sym, &state, &game);

			break;
		case SDL_KEYUP:
			handle_keyup(event.key.keysym.sym);

			break;
		}
	}
}

static void resource_init(void)
{
	init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

	load_images();
	load_sound();

	fps_init(60);
}

static void clean_up(void)
{
	dispose_window();
	destroy_image();
	destroy_sound();

	SDL_Quit();
}