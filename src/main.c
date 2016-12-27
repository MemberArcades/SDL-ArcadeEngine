#include "main.h"

#include <stdbool.h>

#include "SDL.h"
#include "SDL_image.h"

#include "window.h"
#include "renderer.h"

/* Иницализация всех ресурсов */
static void resource_init(void);

/* Инициализация всех внутренних структур, необхдимых при запуске игры */
static void game_init(void);

/* Вызывается, когда игра начинается */
static void startgame_init(void);

/* Освобождает все ресурсы */
static void clean_up(void);

/* ... */
static void main_loop(void);

/* В зависимости от текущего состояния, ссылается на соответсвующий обработчик */
static void internal_tick(void);

/* В зависимости от текущего состояния, рендерит соответствующую картинку*/
static void internal_render(void);

/* Обработка всех SDL событий */
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

		/* TODO: internal_tick(); */
		internal_render();

		/* TODO: fps_sleep(); */
	}
}

static void internal_tick(void) {
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
		
	/* Тест window: get_screen() */
	int tick = SDL_GetTicks();
	int i, j, yofs, ofs;

	yofs = 0;
	for (i = 0; i < SCREEN_HEIGHT; ++i)
	{
		for (j = 0, ofs = yofs; j < SCREEN_WIDTH; ++j, ++ofs)
		{
			((unsigned int*)get_screen()->pixels)[ofs] = i * i + j * j + tick;
		}
		yofs += get_screen()->pitch / 4;
	}


	/* Тест renderer: draw_point() */
	/*int tick = SDL_GetTicks();
	for (size_t r = 0; r < 0xFF; ++r)
	{
		for (size_t g = 0; g < 0xFF; ++g)
		{ 
			draw_point(get_screen(), r, g, SDL_MapRGBA(get_screen()->format, r, g, tick, 255));
		}
	}*/

	/* Тест renderer: draw_line() */
	/*draw_line(get_screen(), 10, 128, 250, 128, SDL_MapRGBA(get_screen()->format, 0xFF, 0x00, 0x00, 0xFF));
	draw_line(get_screen(), 10, 256, 250, 256, SDL_MapRGBA(get_screen()->format, 0x00, 0xFF, 0x00, 0xFF));
	draw_line(get_screen(), 10, 384, 250, 384, SDL_MapRGBA(get_screen()->format, 0x00, 0x00, 0xFF, 0xFF));*/
	
	

	/* TODO: [Menu|Game|Pause]_render. 
	*  В main по минимуму SDL кода, 
	*  в особенности графики. 
	**/

	/*switch (state)
	{
	case Menu:
		break;
	case Game:
		break;
	case Intermission:
		break;
	}*/

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
		}
	}
}

static void resource_init(void)
{
	init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	/* TODO: load_images(), load_sounds(), load_text().*/
}

static void clean_up(void)
{
	dispose_window();
	/* TODO: dispose_ */

	SDL_Quit();
}
