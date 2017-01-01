#pragma once

typedef enum
{
	GameBeginState,
	GamePlayState,
	GameOverState
} GameState;

typedef struct
{
	GameState game_state;
} Game;

void game_init(Game *game);

void game_tick(Game *game);

void game_render(Game *game);
