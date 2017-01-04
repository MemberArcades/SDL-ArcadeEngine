#include "gamescore.h"


static Score score;

static bool initScore = true;


void add_game_score(int points)
{
	score.current += points;

	if (score.current > score.high)
	{
		score.newHigh = true;
	}
}

void init_game_score()
{
	score.current = 0;

	if (initScore)
	{
		score.high = 0;

		initScore = false;
	}

	score.newHigh = false;
}

Score* get_score()
{
	return &score;
}

void check_high_score()
{
	if (score.newHigh)
	{
		score.high = score.current;
	}
}