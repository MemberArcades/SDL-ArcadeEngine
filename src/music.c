#include "music.h"

static Mix_Music *currentSound = NULL;

static int volume = MIX_MAX_VOLUME;


static Mix_Music* load_music(char *filename);

static void sound_volum_minus();

static void sound_volum_plus();

static void sound_off();

static void sound_pause();


static Mix_Music* load_music(char *filename)
{
	Mix_Music *newSound;

	newSound = Mix_LoadMUS(filename);

	if (newSound == NULL)
	{
		printf("Failed to load music! %s\n", filename);

		exit(1);
	}

	return newSound;
}

void load_sound()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("Error load_sound");

		exit(1);
	}

	currentSound = load_music(DIR_SOUND "tetris.wav");

	sound_pause();
}

static void sound_pause()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(currentSound, -1);
		Mix_VolumeMusic(15);
		volume = 15;
	}
	else
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
}

static void sound_off()
{
	Mix_HaltMusic();
}

static void sound_volum_plus()
{
	if (volume < MIX_MAX_VOLUME - VOLUME_STEP)
	{
		volume += VOLUME_STEP;
	}

	Mix_VolumeMusic(volume);
}

static void sound_volum_minus()
{
	if (volume > VOLUME_STEP - 1)
	{
		volume -= VOLUME_STEP;
	}

	Mix_VolumeMusic(volume);
}

void sound_key(int key)
{
	switch (key)
	{
	case SDLK_0:
		sound_off();
		break;
	case SDLK_KP_PLUS:
		sound_volum_plus();
		break;
	case SDLK_KP_MINUS:
		sound_volum_minus();
		break;
	case SDLK_9:
		sound_pause();
		break;
	}
}