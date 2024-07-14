#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <raylib.h>

typedef struct Sound_Manager {
	Sound* sound_gun;
	Sound* sound_crows;
	Sound* sound_crow_die;
	Sound sound_lose;
	Sound sound_click;
	Sound music;
} Sound_Manager;

Sound_Manager* init_sound_manager();
void play_sound_crow_die(Sound_Manager* sound_manager);
void play_sound_gun(Sound_Manager* sound_manager);

#endif