#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/game.h"
#include "include/types.h"
#include "include/scarecrow.h"
#include "include/texture_manager.h"

Texture_Manager* tex_manager = (void*)0;
Scarecrow* scarecrow = (void*)0;

void init()
{
	tex_manager = init_texture_manager();
	scarecrow = init_scarecrow(24, 300, tex_manager->tex_scarecrow.width * SIZE_MULTIPLIER, tex_manager->tex_scarecrow.height * SIZE_MULTIPLIER,
								tex_manager->tex_gun.width * SIZE_MULTIPLIER, tex_manager->tex_gun.height * SIZE_MULTIPLIER);
}

void update()
{
	update_scarecrow(scarecrow);
}

void late_update()
{
	draw_scarecrow(scarecrow, tex_manager);
}

void finish()
{

}