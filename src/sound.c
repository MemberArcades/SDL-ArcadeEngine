#include "sound.h"

static Mix_Music *currentSound = NULL;

static int volume = MIX_MAX_VOLUME;


static Mix_Music* load_sound_file(char *filename);


static Mix_Music* load_sound_file(char *filename)
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

/* Загружает музыкальные ресурсы */
void load_sound()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("Error load_sound");

		exit(1);
	}

	currentSound = load_sound_file(DIR_SOUND "sound.wav");

	sound_pause();
}

/* При вызове ставит музыку на паузу/снимает с паузы,
если она была не включена, то включает */
void sound_pause()
{
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(currentSound, -1);
		Mix_VolumeMusic(VOLUME_START);

		volume = VOLUME_START;
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

/* Отключает музыку */
void sound_off()
{
	Mix_HaltMusic();
}

/* Увеличивает громкость */
void sound_volum_plus()
{
	if (volume < MIX_MAX_VOLUME - VOLUME_STEP)
	{
		volume += VOLUME_STEP;
	}

	Mix_VolumeMusic(volume);
}

/* Уменьшает громкость */
void sound_volum_minus()
{
	if (volume > VOLUME_STEP - 1)
	{
		volume -= VOLUME_STEP;
	}

	Mix_VolumeMusic(volume);
}
