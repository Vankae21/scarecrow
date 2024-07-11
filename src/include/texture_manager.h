#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <raylib.h>

typedef struct Texture_Manager {
	Texture2D tex_scarecrow;
	Texture2D tex_crow;
	Texture2D tex_background0, tex_background1;
	Texture2D tex_bullet;
	Texture2D tex_gun;
	Texture2D tex_hp0, tex_hp1;
} Texture_Manager;

Texture_Manager* init_texture_manager();
void draw_background0(Texture_Manager* tex_manager);
void draw_background1(Texture_Manager* tex_manager);

#endif