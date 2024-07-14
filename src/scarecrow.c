#include "include/scarecrow.h"
#include "include/game.h"
#include <stdlib.h>

Scarecrow* init_scarecrow(f32 x, f32 y, f32 width, f32 height, f32 gun_radius)
{
	Scarecrow* scarecrow = calloc(1, sizeof(Scarecrow));

	// SCARECROW
	scarecrow->pos = (Vector2){ x, y };
	scarecrow->hitbox = (Vector2){ width, height };
	scarecrow->rec = (Rectangle){ x, y, width, height };
	scarecrow->gun = init_gun(x + width * 0.9, y + height/2, gun_radius, 16, 12, 1500);

	return scarecrow;
}

void update_scarecrow(Scarecrow* scarecrow, Sound_Manager* sound_manager)
{
	update_gun(scarecrow->gun, sound_manager);
}

void draw_scarecrow(Scarecrow* scarecrow, Texture_Manager* tex_manager)
{
	Texture2D tex = tex_manager->tex_scarecrow;
	DrawTexturePro(tex, (Rectangle){ 0, 0, tex.width, tex.height }, scarecrow->rec, (Vector2){0}, 0, WHITE);
	if (DEBUG)
		DrawRectangleLinesEx(scarecrow->rec, 1, RED);

	draw_gun(scarecrow->gun, tex_manager);
}