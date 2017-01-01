#pragma once

#include "player.h"
#include "enemy.h"

#define MAX_ENEMIES 16

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
	Enemy enemy[16];
} Game;

void game_init(Game *game);

void game_tick(Game *game);

void game_render(Game *game);
