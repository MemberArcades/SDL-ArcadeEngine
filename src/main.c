#include "main.h"

#include <stdbool.h>

#include "SDL.h"
#include "SDL_image.h"

#include "window.h"
#include "renderer.h"
#include "imageloader.h"
#include "fpsmanager.h"
#include "input.h"

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

static ProgramState state;

static bool gameRunning = true;

int main(int argc, char* args[])
{
	resource_init();

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
	case Menu:
		break;
	case Game:
		break;
	case Intermission:
		break;
	}
}

static void internal_render(void)
{
	clear_screen(0xFF, 0xFF, 0xFF, 0xFF);

	switch (state)
	{
	case Menu:
		break;
	case Game:
		break;
	case Intermission:
		break;
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
			handle_keydown(event.key.keysym.sym);

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

	fps_init(60);

	/* TODO: load_images(), load_sounds(), load_text().*/
}

static void clean_up(void)
{
	dispose_window();
	/* TODO: dispose_ */

	SDL_Quit();
}
