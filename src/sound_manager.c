#include "include/sound_manager.h"
#include <stdlib.h>

Sound_Manager* init_sound_manager()
{
	Sound_Manager* s_manager = calloc(1, sizeof(Sound_Manager));

	s_manager->sound_crows = calloc(3, sizeof(Sound));
	s_manager->sound_crows[0] = LoadSound("assets/crows.ogg");
	s_manager->sound_crows[1] = LoadSound("assets/crows1.ogg");
	s_manager->sound_crows[2] = LoadSound("assets/crows2.ogg");

	s_manager->sound_crow_die = calloc(3, sizeof(Sound));
	s_manager->sound_crow_die[0] = LoadSound("assets/crow_die.ogg"); SetSoundVolume(s_manager->sound_crow_die[0], 0.4f);
	s_manager->sound_crow_die[1] = LoadSound("assets/crow_die.ogg"); SetSoundVolume(s_manager->sound_crow_die[1], 0.4f);
	s_manager->sound_crow_die[2] = LoadSound("assets/crow_die.ogg"); SetSoundVolume(s_manager->sound_crow_die[2], 0.4f);

	s_manager->sound_click = LoadSound("assets/click.wav");
	s_manager->sound_lose = LoadSound("assets/lose.ogg");
	s_manager->music = LoadSound("assets/d_major.ogg"); SetSoundVolume(s_manager->music, 0.13f);

	s_manager->sound_gun = calloc(3, sizeof(Sound));
	s_manager->sound_gun[0] = LoadSound("assets/laserShoot.wav"); SetSoundVolume(s_manager->sound_gun[0], 0.2f);
	s_manager->sound_gun[1] = LoadSound("assets/laserShoot.wav"); SetSoundVolume(s_manager->sound_gun[1], 0.2f);
	s_manager->sound_gun[2] = LoadSound("assets/laserShoot.wav"); SetSoundVolume(s_manager->sound_gun[2], 0.2f);

	return s_manager;
}

void play_sound_crow_die(Sound_Manager* sound_manager)
{
	Sound* sounds = sound_manager->sound_crow_die;
	for (int i = 0; i < 3; i++) {
		if (!IsSoundPlaying(sounds[i])) {
			PlaySound(sounds[i]);
			return;
		}
	}
}

void play_sound_gun(Sound_Manager* sound_manager)
{
	Sound* sounds = sound_manager->sound_gun;
	for (int i = 0; i < 3; i++) {
		if (!IsSoundPlaying(sounds[i])) {
			PlaySound(sounds[i]);
			return;
		}
	}
}