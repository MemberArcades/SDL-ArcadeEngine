#pragma once

#include "imageloader.h"
#include "window.h"
#include "main.h"
#include "game.h"

#include <stdbool.h>


#define X_SHIFT 150
#define Y_SHIFT 28

#define X_MENU_POS 100
#define Y_MENU_POS 300

#define DST_RECT(X, Y) SDL_Rect dstrect = { (X), (Y) };


typedef enum
{
	Start,
	NewGame,
	Options,
	Exit,
	Music
} MainMenu;


void draw_menu();

void menu_key(int key, enum ProgramState *state, Game *game);