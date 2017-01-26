#pragma once

#define _USE_MATH_DEFINES

#include <stdbool.h>
#include <math.h>
#include <stdio.h>


typedef struct 
{
	double x;
	double y;
} Vector;

enum {
	LEFT,
	RIGHT,
	BEYOND,
	BEHIND,
	BETWEEN,
	ORIGIN,
	DESTINATION
};

void print_vector(Vector v);

void add_vector(Vector *v, Vector u);

Vector sum_vector(Vector v, Vector u);

Vector sub_vector(Vector v, Vector u);

void mul_vector(Vector *v, double n);

double  magnitude_vector(Vector v);

void normalise_vector(Vector *v);

void rotate_vector(Vector *v, double degrees);

/* ������������ �������� ���� ������������, ����������� �� ��������� ����� ������������ �������
*
* enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
*       �����, ������, �������, ������, �����,   ������, �����
*
*\param p: �����
*\param e0, e1: ������ � ����� �������
*/
int classify(Vector p, Vector e0, Vector e1);

/* ���������� �������������� ����� �������� */
bool point_in_triangle(Vector p, Vector a, Vector b, Vector c);