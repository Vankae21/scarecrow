#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <raylib.h>

typedef struct Texture_Manager {
	Texture2D tex_scarecrow;
	Texture2D tex_crow;
	Texture2D tex_background;
	Texture2D tex_bullet;
	Texture2D tex_gun;
} Texture_Manager;

Texture_Manager* init_texture_manager();

#endif