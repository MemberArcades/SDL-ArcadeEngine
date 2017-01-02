#pragma once

#include <stdbool.h>

typedef enum
{
	GameBeginState,
	GamePlayState,
	GameOverState
} GameState;

typedef struct
{
	GameState game_state;
	int game_score;
} Game;

void game_init(Game *game);

void game_tick(Game *game);

void game_render(Game *game);

bool game_over(Game *game);

void game_quit();

bool gmae_delay();