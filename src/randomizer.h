#pragma once

#include "main.h"
#include "vector.h"

#include <time.h>

void randomizer_init();

int rand_int(int ceil);

double rand_fract();

int rand_sign();

Vector rand_pos();

Vector rand_dir();