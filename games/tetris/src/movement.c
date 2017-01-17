#include "movement.h"

#include "input.h"
#include "rotation.h"
#include "menu.h"


static int speed = 0;

static int sumSpeed = 1;

static int boost = 0;

static int sumBoost = 0;


static void dir_move(Move *move, Direction direction);

static bool add_boost();

static bool add_speed();


int* get_sum_boost()
{
	return &sumBoost;
}

bool check_movement()
{
	for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
	{
		for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
		{
			if (get_main_field()[i][j].status == Moves)
			{
				return true;
			}
		}
	}

	return false;
}

static void dir_move(Move *move, Direction direction)
{
	switch (direction)
	{
	case Up:
		move->u = 1;
		break;
	case Right:
		move->r = 1;
		break;
	case Down:
		move->d = 1;
		break;
	case Left:
		move->l = 1;
		break;
	}
}

bool check_move(Direction direction)
{
	Move move = { 0, 0, 0, 0 };
	dir_move(&move, direction);

	bool flag = false;

	for (int j = 0; j < Y_MAIN_FIELD_SIZE; ++j)
	{
		for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
		{
			if (get_main_field()[i][j].status == Moves)
			{
				flag = true;

				if ((i - move.l < 0) || (i + move.r > X_MAIN_FIELD_SIZE - 1) || 
					(j - move.u < 0) || (j + move.d > Y_MAIN_FIELD_SIZE - 1) ||
					get_main_field()[i + move.r - move.l][j + move.d - move.u].status == Basis)
				{
					return false;
				}
			}
		}
	}
	

	return flag;
}

void move_toward(Direction direction)
{
	if (check_move(direction))
	{
		Move move = { 0, 0, 0, 0 };
		dir_move(&move, direction);
		
		reboot_rotatoin_index(direction);

		switch (direction)
		{
		case Up:
		case Left:
		{
			for (int j = move.u; j < Y_MAIN_FIELD_SIZE; ++j)
			{
				for (int i = move.l; i < X_MAIN_FIELD_SIZE; ++i)
				{
					if (get_main_field()[i][j].status == Moves)
					{
						recolor_block_main_field(get_main_field()[i][j].color, Moves, i - move.l, j - move.u);
						recolor_block_main_field(BackgroundColor, Background, i, j);
					}
				}
			}

			break;
		}
		case Right:
		case Down:
		{
			for (int j = Y_MAIN_FIELD_SIZE - 1 - move.d; j >= 0; --j)
			{
				for (int i = X_MAIN_FIELD_SIZE - 1 - move.r; i >= 0; --i)
				{
					if (get_main_field()[i][j].status == Moves)
					{
						recolor_block_main_field(get_main_field()[i][j].color, Moves, i + move.r, j + move.d);
						recolor_block_main_field(BackgroundColor, Background, i, j);
					}
				}
			}

			break;
		}
		}
	}
	else
	{
		if (direction == Down)
		{
			moves_to_basis();
		}
	}
}

static bool add_boost()
{
	if (boost < BOOST)
	{
		++boost;

		return false;
	}

	if (sumSpeed + sumBoost < MAX_SPEED)
	{
		++sumBoost;
	}

	boost = 0;

	return true;
}

static bool add_speed()
{
	if (speed < DOWN_SPEED)
	{
		speed += sumSpeed + sumBoost;

		return false;
	}

	speed = 0;

	return true;
}

void move_down()
{
	if (key_held(SDLK_DOWN) || key_held(SDLK_s))
	{
		speed += 10;
	}

	if (add_speed())
	{
		move_toward(Down);
	}

	add_boost();
}

void movement_dir_button(int key)
{
		if (pushed_right(key))
		{
			move_toward(Right);
		}

		if (pushed_left(key))
		{
			move_toward(Left);
		}
}