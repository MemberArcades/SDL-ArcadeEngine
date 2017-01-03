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
	int high_score;
} Game;

void game_init(Game *game);

void game_tick(Game *game);

void game_render(Game *game);

bool game_over(Game *game);

bool gmae_delay();

void add_game_score(Game *game, int score);

void game_init_score(Game *game);