#pragma once

#include "player.h"
#include "enemy.h"

#define ENEMIES 4

typedef enum
{
	GameBeginState,
	GamePlayState,
	GameOverState
} GameState;

typedef struct
{
	GameState game_state;
	
	Player player;
	Enemy enemy[MAX_ENEMIES];

	int enemies_count;
	int lvl;
} Game;

void game_init(Game *game);

void game_tick(Game *game);

void game_render(Game *game);
