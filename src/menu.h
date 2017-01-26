#pragma once

#include <stdbool.h>

#include "input.h"
#include "main.h"
#include "renderer.h"
#include "window.h"
#include "enemy.h"

#define ENEMIES 8


typedef enum
{
	Nothing,
	GoToGame
} MenuAction;

typedef struct
{
	MenuAction action;
	unsigned int ticksSinceModeChange;

	Enemy enemy[MAX_ENEMIES];
} MenuSystem;

void menu_tick(MenuSystem *menuSystem);

void menu_render(MenuSystem *menuSystem);

void menu_init(MenuSystem *menuSystem);