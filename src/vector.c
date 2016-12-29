#include "vector.h"

#include <math.h>
#include <stdio.h>

void print_vector(Vector v)
{
	printf("%f %f\n", v.x, v.y);
}

void add_vector(Vector *v, Vector u)
{
	v->x += u.x;
	v->y += u.y;
}

Vector sum_vector(Vector v, Vector u)
{
	return (Vector) { v.x + u.x, v.y + u.y };
}

void mul_vector(Vector *v, double n)
{
	v->x *= n;
	v->y *= n;
}

double  magnitude_vector(Vector v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

void normalise_vector(Vector *v)
{
	double magnitude = magnitude_vector(*v);
	v->x /= magnitude;
	v->y /= magnitude;
}

void rotate_vector(Vector *v, double degrees)
{
	double angle = degrees * M_PI / 180;
	double rot_matrix[2][2] = {
		{cos(angle), -sin(angle)},
		{sin(angle), cos(angle)}
	};
	
	double x = v->x;
	double y = v->y;

	v->x = x * rot_matrix[0][0] + y * rot_matrix[0][0];
	v->y = x * rot_matrix[1][0] + y * rot_matrix[1][0];
}
