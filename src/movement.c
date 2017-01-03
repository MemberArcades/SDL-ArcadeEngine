#include "movement.h"
#include "input.h"
#include "rotation.h"

static int downSpeed = 0;

static int leftSpeed = 0;

static int rightSpeed = 0;

static int speed = 1;


static Direction get_movement_dir_button();

static void dir_move(Move *move, Direction direction);


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
	if (direction == Down)
	{
		if (downSpeed < 20)
		{
			downSpeed += speed;

			return;
		}
		else
		{
			downSpeed = 0;
		}
	}


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

static Direction get_movement_dir_button()
{
	if (key_held(SDLK_w) == KeyDown || key_held(SDLK_UP) == KeyDown)
	{
		if (key_held(SDLK_w) == KeyDown)
		{
			handle_keydown(SDLK_w);
		}
		else
		{
			handle_keydown(SDLK_UP);
		}

		return Up;
	}

	if (key_held(SDLK_d) == KeyDown || key_held(SDLK_RIGHT) == KeyDown)
	{
		if (key_held(SDLK_d) == KeyDown)
		{
			handle_keydown(SDLK_d);
		}
		else
		{
			handle_keydown(SDLK_RIGHT);
		}

		return Right;
	}

	if (key_held(SDLK_a) == KeyDown || key_held(SDLK_LEFT) == KeyDown)
	{
		if (key_held(SDLK_a) == KeyDown)
		{
			handle_keydown(SDLK_a);
		}
		else
		{
			handle_keydown(SDLK_LEFT);
		}

		return Left;
	}

	if (key_held(SDLK_s) == KeyDown || key_held(SDLK_DOWN) == KeyDown)
	{
		/* Отключение ограничение на движение вниз */
		/*if (key_held(SDLK_s) == KeyDown)
		{
			handle_keydown(SDLK_s);
		}
		else
		{
			handle_keydown(SDLK_DOWN);
		}*/

		downSpeed += speed * 5;

		return Down;
	}

	printf("get_movement_dir_button Error\n");
	exit(1);
}

void movement_dir_button()
{
	if (check_key_movement_pressed())
	{
		if (key_held(SDLK_d) == KeyDown || key_held(SDLK_RIGHT) == KeyDown)
		{
			if (rightSpeed <= SIDES_SPEED)
			{
				++rightSpeed;
			}
			else
			{
				rightSpeed = 0;
				move_toward(Right);
			}
		}

		if (key_held(SDLK_a) == KeyDown || key_held(SDLK_LEFT) == KeyDown)
		{
			if (leftSpeed <= SIDES_SPEED)
			{
				++leftSpeed;
			}
			else
			{
				leftSpeed = 0;
				move_toward(Left);
			}
		}

		if (key_held(SDLK_s) == KeyDown || key_held(SDLK_DOWN) == KeyDown)
		{
			downSpeed += speed + 5;

			move_toward(Down);
		}
		//move_toward(get_movement_dir_button());
	}
}

void blocks_to_moves(int border)
{
	for (int j = 0; j < border; ++j)
	{
		for (int i = 0; i < X_MAIN_FIELD_SIZE; ++i)
		{
			if (get_main_field()[i][j].status != Background)
			{
				get_main_field()[i][j].status = Moves;
			}
		}
	}
}