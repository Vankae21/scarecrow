#include "include/scarecrow.h"
#include "include/game.h"
#include <math.h>
#include <stdlib.h>
#include "include/vutils.h"

Scarecrow* init_scarecrow(f32 x, f32 y, f32 width, f32 height, f32 gun_width, f32 gun_height)
{
	Scarecrow* scarecrow = calloc(1, sizeof(Scarecrow));

	// SCARECROW
	scarecrow->pos = (Vector2){ x, y };
	scarecrow->hitbox = (Vector2){ width, height };
	scarecrow->rec = (Rectangle){ x, y, width, height };
	scarecrow->gun = init_gun(x + width, y + height/2, gun_width, gun_height, 16, 16, 100);

	return scarecrow;
}

void update_scarecrow(Scarecrow* scarecrow)
{
	update_gun(scarecrow->gun);
}

void draw_scarecrow(Scarecrow* scarecrow, Texture_Manager* tex_manager)
{
	Texture2D tex = tex_manager->tex_scarecrow;
	DrawTexturePro(tex, (Rectangle){ 0, 0, tex.width, tex.height }, scarecrow->rec, (Vector2){0}, 0, WHITE);
	DrawRectangleLinesEx(scarecrow->rec, 2, RED);

	draw_gun(scarecrow->gun, tex_manager);
}