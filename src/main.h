#pragma once

#define SCREEN_TITLE "Tetris"
#define SCREEN_WIDTH 540
#define SCREEN_HEIGHT 742


/* Состояния, в которых может быть игра */
typedef enum
{
	Menu, 
	Play, 
	Pause,
	End
} ProgramState;

