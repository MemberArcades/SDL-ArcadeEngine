#pragma once

#include "game.h"

#include <stdbool.h>

#define FILE_SCORE "gamescore.txt"


typedef struct
{
	bool newHigh;
	unsigned long long current;
	unsigned long long high;
} Score;


void add_game_score(unsigned long long points);

void init_game_score();

Score* get_score();

void check_high_score();