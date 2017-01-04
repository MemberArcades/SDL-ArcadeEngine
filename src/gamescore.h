#pragma once

#include "game.h"

#include <stdbool.h>


typedef struct
{
	bool newHigh;
	int high;
	int current;
} Score;


void add_game_score(int points);

void init_game_score();

Score* get_score();

void check_high_score();