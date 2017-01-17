#pragma once

#include <stdbool.h>


typedef enum
{
	GamePlayState,
	GamePauseState
} GameState;

typedef struct
{
	GameState game_state;
} Game;


void game_init(Game *game);

void game_tick(Game *game);

bool game_over(Game *game);
