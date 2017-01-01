#include "enemy.h"
#include "vector.h"

#include <time.h>
#include <stdlib.h>

Vector bodies[3][12] = {
	{ { 0, 10 },{ 12, 0 },{ 23, 13 },{ 32, 0 },{ 45, 10 },{ 36, 20 },{ 45, 30 },{ 30, 40 },{ 13, 40 },{ 0, 30 },{ 0, 30 },{ 0, 30 } },
	{ { 10, 0 },{ 20, 7 },{ 30, 0 },{ 40, 10 },{ 30, 13 },{ 40, 20 },{ 32, 40 },{ 18, 30 },{ 10, 40 },{ 0, 30 },{ 5, 20 },{ 0, 10 } },
	{ { 10, 0 },{ 27, 0 },{ 40, 10 },{ 27, 20 },{ 40, 30 },{ 33, 40 },{ 27, 36 },{ 10, 40 },{ 0, 25 },{ 0, 10 },{ 17, 10 },{ 17, 10 } },
};

void enemy_init(Enemy *enemy, Vector position, Vector direction, double velocity, int body_type)
{
	enemy->body.position = position;
	enemy->body.direction = direction;
	enemy->body.velocity = velocity;

	enemy->body.collider.points_count = 12;

	for (int i = 0; i < 12; ++i)
		enemy->body.collider.points[i] = bodies[body_type][i];
}

void enemies_init(Enemy enemies[], int n)
{
	int nStartValue = time(NULL);
	srand(nStartValue);
	
	for (int i = 0; i < n; ++i)
	{
		Vector pos = { rand() % SCREEN_WIDTH, rand() % SCREEN_WIDTH };
		Vector dir = { (rand() % 10) / 10.0, (rand() % 10) / 10.0 };
		normalise_vector(&dir);
		int body_type = rand() % 3;

		enemy_init(&enemies[i], pos, dir, 1, body_type);
	}
}