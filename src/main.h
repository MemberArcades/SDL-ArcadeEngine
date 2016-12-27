#pragma once

#define SCREEN_TITLE "Asteroids"
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 640


/* состояния, в которых может быть программа */
typedef enum
{
	Menu, 
	Game, 
	Intermission,
} ProgramState;

