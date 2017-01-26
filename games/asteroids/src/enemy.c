#include "enemy.h"


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

		if (size == 2)
			mul_vector(&temp, 0.61);
		else if (size == 1)
			mul_vector(&temp, 0.37);

		enemy->body.collider.points[i] = temp;
	}
}

void enemies_init(Enemy enemies[], int n)
{
	time_t nStartValue = time(NULL);
	srand(nStartValue);
	
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		int pos_rand = rand_int(4);
		Vector pos;
		/* Астероиды должны появляться только по краям экрана, чтобы случайно не убить игрока*/
		switch (pos_rand)
		{
		case 0:
			pos = rand_pos();
			pos.y = 0;

			break;
		case 1:
			pos = rand_pos();
			pos.x = SCREEN_WIDTH;

			break;
		case 2:
			pos = rand_pos();
			pos.y = SCREEN_HEIGHT;

			break;
		case 3	:
			pos = rand_pos();
			pos.x = 0;

			break;
		default:
			pos = rand_pos();

			break;
		}
		

		Vector dir = rand_dir();

		int body_type = rand_int(3);

		enemy_init(&enemies[i], pos, dir, 0.41, body_type, 3);

		if (i >= n)
			enemies[i].alive = false;
	}
}

int enemy_boom(Enemy *shoted_enemy, Enemy enemies[])
{
	enemy_remove(shoted_enemy);

	int shoted_enemy_size = shoted_enemy->size;
	double shoted_enemy_vel = shoted_enemy->body.velocity;

	if (shoted_enemy_size <= 1)
		return -1;

	/* Найти первую свободную ячейку */
	int needed = 2; /*(shoted_enemy_size == 3) ? (2 + rand_int(3)) : (rand_int(4)); */
	int count = 0;

	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (needed == count)
			break;

		if (!enemies[i].alive)
		{ 
			Vector dir = rand_dir();

			enemy_init(&enemies[i], shoted_enemy->body.position, dir, shoted_enemy_vel * 1.62, shoted_enemy->body_type, shoted_enemy_size - 1);
			
			++count;
		}
	}

	return count - 1;
}

void enemy_remove(Enemy *enemy)
{
	enemy->alive = false;
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