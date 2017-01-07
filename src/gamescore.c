#define _CRT_SECURE_NO_WARNINGS

#include "gamescore.h"


#include "renderer.h"


#include <stdio.h>
#include <stdbool.h>



static Score score;

static bool initScore = true;

static FILE *file;

static char highScore[30];
static char currentScore[30];


static bool open_file_score();

static bool record_high_score();


static bool open_file_score()
{
	if ((file = fopen(FILE_SCORE, "r")) == NULL || feof(file))
	{
		return false;
	}

	fread(highScore, sizeof(char), 20, file);

	int i = 0;

	score.high = 0;

	while (highScore[i] && (highScore[i] <= '9') && ('0' <= highScore[i]))
	{
		score.high = score.high * 10 + highScore[i] - '0';
		++i;
	}

	fclose(file);

	return true;
}

void add_game_score(unsigned long long points)
{
	score.current += points;

	if (score.current > score.high)
	{
		score.newHigh = true;
	}

	sprintf(currentScore, "%llu", score.current);
	draw_text(currentScore, (Point) { 102, 35 });
}

void init_game_score()
{
	score.current = 0;

	if (initScore)
	{
		if (!open_file_score())
		{
			score.high = 0;
		}

		initScore = false;
	}

	draw_text("High score:", (Point) { 13, 13 });
	draw_high_score();

	draw_text("You score:", (Point) { 13, 35 });
	draw_text("0", (Point) { 102, 35 });

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

		record_high_score();

		draw_text(highScore, (Point) { 102, 14 });
	}
}

static bool record_high_score()
{
	if ((file = fopen(FILE_SCORE, "w")) == NULL)
	{
		printf("Error create: " FILE_SCORE);

		return false;
	}

	fprintf(file, "%llu", score.high);

	fclose(file);

	return true;
}

void draw_high_score()
{
	sprintf(highScore, "%llu", score.high);
	draw_text(highScore, (Point) { 102, 14 });
}