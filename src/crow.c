#include "include/crow.h"
#include "include/game.h"
#include "include/vutils.h"
#include <stdlib.h>

Crow* init_crow(Vector2 pos, f32 radius, f32 speed)
{
	Crow* crow = calloc(1, sizeof(Crow));

	crow->pos = pos;
	crow->radius = radius;
	crow->speed = speed;
	crow->state = FLYING;
	crow->frame = CROW_MIN_FLYING_FRAME;
	crow->frame_timer = 0;

	return crow;
}

void update_crow(Crow* crow)
{
	if (crow->pos.y != CROW_MAX_HEIGHT) {
		crow->pos = vec2_translate(crow->pos, (Vector2){ crow->pos.x, CROW_MAX_HEIGHT }, crow->speed);
	} else {
		crow->state = EATING;
	}

	if (crow->frame_timer < CROW_FRAME_TIME) {
		crow->frame_timer += GetFrameTime();
	} else {
		crow->frame_timer = 0;
		switch(crow->state) {
			case FLYING:
				crow->frame = crow->frame == CROW_MAX_FLYING_FRAME ? CROW_MIN_FLYING_FRAME : crow->frame + 1;
				break;
			case EATING:
				crow->frame = crow->frame == CROW_MAX_EATING_FRAME ? CROW_MIN_EATING_FRAME : crow->frame + 1;
				break;
			default:
				break;
		}
	}
}

void draw_crow(Crow* crow, Texture_Manager* tex_manager)
{
	Texture2D tex = tex_manager->tex_crow;

	DrawTexturePro(tex, (Rectangle){ tex.height * crow->frame, 0, tex.height, tex.height },
				   (Rectangle){ crow->pos.x, crow->pos.y, crow->radius * 2, crow->radius * 2 }, (Vector2){crow->radius, crow->radius}, 0, WHITE);
	DrawCircleLinesV(crow->pos, crow->radius, RED);
}

Crow** init_crows(f32 radius, u16 crow_count)
{
	Crow** crows = calloc(crow_count, sizeof(Crow*));

	u16 spawn_offset_x = 250;
	for (int i = 0; i < crow_count; i++) {
		crows[i] = init_crow((Vector2){ spawn_offset_x - RADIUS_CROW + rand() % (WIDTH - spawn_offset_x), -radius },
							 radius, random_val(CROW_MIN_SPEED, CROW_MAX_SPEED));
	}

	return crows;
}

void update_crows(Crow** crows, u16 crow_count)
{
	for (int i = 0; i < crow_count; i++) {
		update_crow(crows[i]);
	}
}

void draw_crows(Crow** crows, u16 crow_count, Texture_Manager* tex_manager)
{
	for (int i = 0; i < crow_count; i++) {
		draw_crow(crows[i], tex_manager);
	}
}

void add_to_crows(Crow*** crows, u16* crow_count, Vector2 pos)
{
	(*crow_count)++;
	*crows = realloc(*crows, *crow_count * (sizeof(Crow*)));
	(*crows)[*crow_count - 1] = init_crow(pos, RADIUS_CROW, random_val(CROW_MIN_SPEED, CROW_MAX_SPEED));
}

void remove_from_crows(Crow*** crows, u16* crow_count, Crow* crow)
{
	u16 c = 0;
	Crow** result = (void*)0;

	for (int i = 0; i < *crow_count; i++) {
		if ((*crows)[i] == crow) {
			free(crow);
			continue;
		}
		c++;
		result = realloc(result, (sizeof(Crow*) * c));
		result[c - 1] = (*crows)[i];
	}
	free(*crows);
	*crows = result;
	*crow_count = c;
}