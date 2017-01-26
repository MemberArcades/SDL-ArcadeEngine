#include "vector.h"


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

Vector sub_vector(Vector v, Vector u)
{
	return (Vector) { v.x - u.x, v.y - u.y };
}

void mul_vector(Vector *v, double n)
{
	v->x *= n;
	v->y *= n;
}

double magnitude_vector(Vector v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

void normalise_vector(Vector *v)
{
	double magnitude = magnitude_vector(*v);
	v->x /= magnitude;
	v->y /= magnitude;
}

bool equal_vector(Vector v, Vector u)
{
	return (v.x == u.x && v.y == u.y);
}

void rotate_vector(Vector *v, double degrees)
{
	double angle = degrees * M_PI / 180;
	double rot_matrix[2][2] = {
		{ cos(angle), -sin(angle) },
		{ sin(angle), cos(angle) }
	};

	double x = v->x;
	double y = v->y;

	v->x = x * rot_matrix[0][0] + y * rot_matrix[0][1];
	v->y = x * rot_matrix[1][0] + y * rot_matrix[1][1];
}

int classify(Vector p, Vector e0, Vector e1)
{
	Vector a = sub_vector(e1, e0);
	Vector b = sub_vector(p, e0);

	double sa = a.x * b.y - b.x * a.y;

	if (sa > 0.0)
		return LEFT;
	if (sa < 0.0)
		return RIGHT;
	if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0))
		return BEHIND;
	if (magnitude_vector(a) < magnitude_vector(b))
		return BEYOND;
	if (equal_vector(e0, p))
		return ORIGIN;
	if (equal_vector(e1, p))
		return DESTINATION;

	return BETWEEN;
}

bool point_in_triangle(Vector p, Vector a, Vector b, Vector c)
{
	return ((classify(p, a, b) != LEFT) &&
		(classify(p, b, c) != LEFT) &&
		(classify(p, c, a) != LEFT));
}