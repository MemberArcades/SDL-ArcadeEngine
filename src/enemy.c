#include "enemy.h"
#include "vector.h"

#include <time.h>
#include <stdlib.h>

Vector bodies[3][12] = {
	{ { 0, 10 },{ 12, 0 },{ 23, 13 },{ 32, 0 },{ 45, 10 },{ 36, 20 },{ 45, 30 },{ 30, 40 },{ 13, 40 },{ 0, 30 },{ 0, 30 },{ 0, 30 } },
	{ { 10, 0 },{ 20, 7 },{ 30, 0 },{ 40, 10 },{ 30, 13 },{ 40, 20 },{ 32, 40 },{ 18, 30 },{ 10, 40 },{ 0, 30 },{ 5, 20 },{ 0, 10 } },
	{ { 10, 0 },{ 27, 0 },{ 40, 10 },{ 27, 20 },{ 40, 30 },{ 33, 40 },{ 27, 36 },{ 10, 40 },{ 0, 25 },{ 0, 10 },{ 17, 10 },{ 17, 10 } },
};

void enemy_init(Enemy *enemy, Vector position, Vector direction, double velocity, int body_type, int size)
{
	enemy->alive = true;
	enemy->size = size;
	enemy->body_type = body_type;

	enemy->body.position = position;
	enemy->body.direction = direction;
	enemy->body.velocity = velocity;

	enemy->body.collider.points_count = 12;

	for (int i = 0; i < 12; ++i){
		Vector temp = bodies[body_type][i]; 
		enemy->body.collider.points[i] = temp;
	}
}

void enemies_init(Enemy enemies[], int n)
{
	int nStartValue = time(NULL);
	srand(nStartValue);
	
	for (int i = 0; i < n; ++i)
	{
		int pos_rand = rand() % 2;
		Vector pos;

		switch (pos_rand)
		{
		case 0:
			pos = (Vector) { rand() % SCREEN_WIDTH, 0 };
			break;
		case 1:
			pos = (Vector) { SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
			break;
		case 2:
			pos = (Vector) { rand() % SCREEN_WIDTH, SCREEN_HEIGHT };
			break;
		case 3	:
			pos = (Vector) { 0, rand() % SCREEN_HEIGHT };
			break;
		default:
			pos = (Vector) { rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT };
			break;
		}
		

		int sign_rand_x = (rand() % 2 == 1) ? (1) : (-1);
		int sign_rand_y = (rand() % 2 == 1) ? (1) : (-1);
		
		Vector dir = { (rand() % 100) / 100.0 * sign_rand_x, (rand() % 100) / 100.0 * sign_rand_y };
		normalise_vector(&dir);

		int body_type = rand() % 3;

		enemy_init(&enemies[i], pos, dir, 1, body_type, 2);
	}
}

void enemy_reset_to_position(Enemy enemies[], Vector position)
{
	/* Найти первую свободную ячейку */
	int i = 0;
	for (i = 0; (enemies[i].alive ||  enemies[i].size < 1) && i < MAX_ENEMIES; ++i);

	/* Нет свободных ячеек */
	if (enemies[i].alive || enemies[i].size < 1)
		return;

	/* Вернуть астероид в указаное место */
	enemies[i].alive = true;
	enemies[i].body.position = position;
	

	
}

void enemy_remove(Enemy *enemy)
{
	enemy->alive = false;

	enemy->size -= 1;
	
	for (int j = 0; j < enemy->body.collider.points_count; ++j)
		mul_vector(&enemy->body.collider.points[j], 0.75);
}

/* Тут я поленился реализовывать crossing number (count) algorithm.
* Поэтому разбил врагов (благо, что их всего 3 типа) на 9 треугольников
* и проверял их на принадлежность точки.
* \triangles - индексы вершин треугольника в ps.body.collider.points[]
*/
bool enemy_collision_with(Enemy enemy, PhysicsBody body)
{
	if (!enemy.alive)
		return false;

	int triangles[3][9][3] = {
		{ { 2, 0, 1 },{ 2, 3, 4 },{ 2, 4, 5 },{ 2, 5, 6 },{ 2, 6, 7 },{ 2, 7, 8 },{ 2, 8, 9 },{ 2, 9, 0 },{ 2, 9, 0 } },
		{ { 1, 2, 3 },{ 1, 3, 4 },{ 1, 4, 5 },{ 1, 5, 6 },{ 1, 6, 7 },{ 1, 7, 8 },{ 1, 8, 9 },{ 1, 9, 10 },{ 1, 10, 11 } },
		{ { 10, 0, 1 },{ 10, 1, 2 },{ 10, 2, 3 },{ 10, 3, 4 },{ 10, 4, 5 },{ 10, 5, 6 },{ 10, 6, 7 },{ 10, 7, 8 },{ 10, 8, 9 } } 
	};

	for (int i = 0; i < body.collider.points_count; ++i)
	{
		Vector p = sum_vector(body.collider.points[i], body.position);
		
		for (int j = 0; j < 9; ++j)
		{
			/* Странная ошибка, когда body_type не определен */
			/*if (enemy.body_type < 0)
				enemy.body_type *= -1;
			enemy.body_type %= 3;*/

			Vector a = sum_vector(enemy.body.collider.points[ triangles[enemy.body_type][j][2] ], enemy.body.position);
			Vector b = sum_vector(enemy.body.collider.points[ triangles[enemy.body_type][j][1] ], enemy.body.position);
			Vector c = sum_vector(enemy.body.collider.points[ triangles[enemy.body_type][j][0] ], enemy.body.position);

			if (point_in_triangle(p, a, b, c))
			{
				return true;
			}
		}
	}

	return false;
}