#pragma once

#include "enemy.h"

#define ENEMIES 8

//Defines what action we should take at a particular time while on the menu.
typedef enum
{
	Nothing,
	GoToGame
} MenuAction;

//Defines the menu system.
typedef struct
{
	MenuAction action;
	unsigned int ticksSinceModeChange;

	Enemy enemy[MAX_ENEMIES];
} MenuSystem;

//Performs a single tick on the menu system.
void menu_tick(MenuSystem *menuSystem);

//Renders the menu system in its current state.
void menu_render(MenuSystem *menuSystem);

void menu_init(MenuSystem *menuSystem);