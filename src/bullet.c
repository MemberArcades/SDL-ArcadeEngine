#include "bullet.h"

void bullet_init(Bullet *bullet, double velocity)
{
	bullet->alive = false;
	bullet->body.position = (Vector) { 0, 0 };
	bullet->body.direction = (Vector) { 0, 1 };
	bullet->body.velocity = velocity;

	bullet->body.collider.points_count = 1;
	bullet->body.collider.points[0] = (Vector) { 0, 0 };
	bullet->body.collider.points[1] = (Vector) { 0, 0 };
}

void bullets_init(Bullet bullets[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		bullet_init(&bullets[i], 4.1);
	}
}

void bullet_shot(Bullet bullets[], Vector pos, Vector dir)
{
	/* Найти первую готовую к выстрелу пулю */
	int i = 0;
	for (i = 0; bullets[i].alive  && i < MAX_BULLETS; ++i);

	/* Нет готовых к выстрелу */
	if (bullets[i].alive)
		return;

	bullets[i].alive = true;
	bullets[i].body.position = pos;

	mul_vector(&dir, bullets[i].body.velocity);
	bullets[i].body.direction = dir;
}

void bullet_remove(Bullet *bullet)
{
	bullet->alive = false;
}