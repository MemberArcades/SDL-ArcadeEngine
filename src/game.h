#pragma once

#include "player.h"

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
} Game;

void game_init(Game *game);

void game_tick(Game *game);

void game_render(Game *game);
