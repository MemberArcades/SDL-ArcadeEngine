#pragma once

#include <math.h>

#include "player.h"
#include "enemy.h"
#include "window.h"
#include "renderer.h"
#include "input.h"

#define ENEMIES 4

typedef enum
{
	GameBeginState,
	GamePlayState,
	GameDeathState,
	GameOverState
} GameState;

typedef struct
{
	GameState game_state;
	
	Player player;

	Enemy enemy[MAX_ENEMIES];
	int enemies_count;

	unsigned last_gamestate_change;
	
	int score;
	int lvl;
} Game;

void game_init(Game *game);

void game_tick(Game *game);

void game_render(Game *game);
