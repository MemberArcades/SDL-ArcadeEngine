#include "fpsmanager.h"

#include "SDL_framerate.h"


static FPSmanager fps_manager;


void fps_init(int frequency)
{
	SDL_initFramerate(&fps_manager);
	fps_set_frequency(frequency);
}

void fps_set_frequency(int frequency)
{
	SDL_setFramerate(&fps_manager, frequency);
}

void fps_sleep(void)
{
	SDL_framerateDelay(&fps_manager);
}
