#pragma once

#define _USE_MATH_DEFINES

typedef struct 
{
	double x;
	double y;
} Vector;

void print_vector(Vector v);

void add_vector(Vector *v, Vector u);

Vector sum_vector(Vector v, Vector u);

void mul_vector(Vector *v, double n);

double  magnitude_vector(Vector v);

void normalise_vector(Vector *v);

void rotate_vector(Vector *v, double degrees);
