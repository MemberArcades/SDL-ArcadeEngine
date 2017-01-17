#include "menu.h"
#include "main.h"
#include "block.h"
#include "input.h"
#include "game.h"
#include "music.h"


static MainMenu menu = Start;


static void draw_menu_start(int pos);

static void draw_menu_new_game(int pos);

static void draw_menu_options(int pos);

static void draw_menu_exit(int pos);

static void draw_menu_music(int pos);

static void draw_menu_background();

static void menu_game_continue(enum ProgramState *state, Game *game);

static void menu_actions_play(int key, enum ProgramState *state, Game *game);

static void menu_actions_menu(int key, enum ProgramState *state);

static void menu_actions_pause(int key, enum ProgramState *state, Game *game);

static void menu_actions_motion(int key);


static bool style = true;


static void draw_menu_start(int pos)
{
	SDL_Rect imgrect = { (Start == menu) * X_SHIFT, 0, X_SHIFT, Y_SHIFT };

	DST_RECT(X_MENU_POS, Y_MENU_POS + pos * Y_SHIFT)

	SDL_BlitSurface(get_menu_text_image(), &imgrect, get_screen(), &dstrect);
}

static void draw_menu_new_game(int pos)
{
	SDL_Rect imgrect = { (NewGame == menu) * X_SHIFT, 3 * Y_SHIFT, X_SHIFT, Y_SHIFT };

	DST_RECT(X_MENU_POS, Y_MENU_POS + pos * Y_SHIFT)

	SDL_BlitSurface(get_menu_text_image(), &imgrect, get_screen(), &dstrect);
}

static void draw_menu_options(int pos)
{
	SDL_Rect imgrect = { (Options == menu) * X_SHIFT, Y_SHIFT, X_SHIFT, Y_SHIFT };

	DST_RECT(X_MENU_POS, Y_MENU_POS + pos * Y_SHIFT)

	SDL_BlitSurface(get_menu_text_image(), &imgrect, get_screen(), &dstrect);
}

static void draw_menu_exit(int pos)
{
	SDL_Rect imgrect = { (Exit == menu) * X_SHIFT, 2 * Y_SHIFT, X_SHIFT, Y_SHIFT };

	DST_RECT(X_MENU_POS, Y_MENU_POS + pos * Y_SHIFT)

	SDL_BlitSurface(get_menu_text_image(), &imgrect, get_screen(), &dstrect);
}

static void draw_menu_music(int pos)
{
	SDL_Rect imgrect = { (Music == menu) * X_SHIFT, 4 * Y_SHIFT, X_SHIFT, Y_SHIFT };

	DST_RECT(X_MENU_POS, Y_MENU_POS + pos * Y_SHIFT)

	SDL_BlitSurface(get_menu_text_image(), &imgrect, get_screen(), &dstrect);
}

static void draw_menu_background()
{
	SDL_Rect dstrect = { X_MAIN_FIELD, Y_MAIN_FIELD };

	SDL_BlitSurface(get_menu_background_image(), NULL, get_screen(), &dstrect);
}

void draw_menu()
{
	draw_menu_background();

	draw_menu_start(0);
	//draw_menu_new_game();
	//draw_menu_options(1);
	draw_menu_music(1);
	draw_menu_exit(2);
}

static void menu_game_continue(ProgramState *state, Game *game)
{
	*state = Play;
	game->game_state = GamePlayState;

	recolor_main_field();
}

static void menu_actions_play(int key, ProgramState *state, Game *game)
{
	if (key == SDLK_ESCAPE)
	{
		*state = Pause;
		game->game_state = GamePauseState;
	}
}

static void menu_actions_pause(int key, ProgramState *state, Game *game)
{
	menu_actions_motion(key);

	if ((key == SDLK_ESCAPE) || (pushed_enter(key) && (menu == Start)))
	{
		menu_game_continue(state, game);

		return;
	}

	if (pushed_enter(key) && (menu == Exit))
	{
		*state = Out;

		return;
	}

	if (pushed_enter(key) && (menu == Music))
	{
		sound();

		return;
	}
}

static void menu_actions_menu(int key, ProgramState *state)
{
	menu_actions_motion(key);

	if (pushed_enter(key))
	{
		switch (menu)
		{
		case Start:
			*state = Play;

			recolor_main_field();

			break;
		case Music:
			sound();

			break;
		case Exit:
			*state = Out;

			break;
		}
	}
}

static void menu_actions_motion(int key)
{
	if (pushed_down(key))
	{
		switch (menu)
		{
		case Start:
			menu = Music;

			break;
		case Music:
			menu = Exit;

			break;
		case Exit:
			menu = Start;

			break;
		}
	}

	if (pushed_up(key))
	{
		switch (menu)
		{
		case Start:
			menu = Exit;

			break;
		case Music:
			menu = Start;

			break;
		case Exit:
			menu = Music;

			break;
		}
	}
}

void menu_key(int key, ProgramState *state, Game *game)
{
	switch (*state)
	{
	case Play:
		menu_actions_play(key, state, game);
		break;
	case Pause:
		menu_actions_pause(key, state, game);
		break;
	case Menu:
		menu_actions_menu(key, state);
		break;
	}
}