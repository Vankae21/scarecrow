#include "include/texture_manager.h"
#include <stdlib.h>

Texture_Manager* init_texture_manager()
{
	Texture_Manager* texture_manager = calloc(1, sizeof(Texture_Manager));

	texture_manager->tex_scarecrow = LoadTexture("assets/scarecrow.png");
	texture_manager->tex_gun = LoadTexture("assets/gun.png");

	return texture_manager;
}