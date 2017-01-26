#include "randomizer.h"

void randomizer_init() {
	time_t start_value = time(NULL);
	srand(start_value);
}

int rand_int(int ceil)
{
	return rand() % (ceil);
}

double rand_fract()
{
	return (rand() % 100) / 100.0;
}

int rand_sign()
{
	return (rand() % 2 == 0) ? (1) : (-1);
}

Vector rand_pos()
{
	return (Vector) { rand() % SCREEN_WIDTH , rand() % SCREEN_HEIGHT };
}

Vector rand_dir()
{
	Vector dir = (Vector) { rand_fract() * rand_sign(), rand_fract() * rand_sign() };
	normalise_vector(&dir);

	return dir;
}