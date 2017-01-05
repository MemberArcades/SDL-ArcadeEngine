#define _CRT_SECURE_NO_WARNINGS

#include "gamescore.h"


#include "renderer.h"


#include <stdio.h>
#include <stdbool.h>



static Score score;

static bool initScore = true;

static FILE *file;


static bool open_file_score();

static bool record_high_score();


static bool open_file_score()
{
	if ((file = fopen(FILE_SCORE, "r")) == NULL || feof(file))
	{
		return false;
	}

	fscanf(file, "%llu", &score.high);

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
}

void draw_high_score(Point dst, Point offset)
{
	unsigned long long copyScore = score.high;

	if (copyScore)
	{
		for (int k = 0; copyScore > 0; copyScore /= 10, k += 1)
		{
			dst.x -= 14;

			draw_number_offset(copyScore % 10, dst, offset);
		}
	}
	else
	{
		draw_number_offset(0, dst, offset);
	}
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

	draw_high_score((Point) { 325, 18 }, (Point) { 0, 0 });

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

		draw_high_score((Point) { 325, 18 }, (Point) { 0, 0 });
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

