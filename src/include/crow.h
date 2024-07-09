#ifndef CROW_H
#define CROW_H

#include <raylib.h>
#include "game.h"
#include "texture_manager.h"
#include "types.h"

#define RADIUS_CROW 32.0f
#define CROW_MAX_HEIGHT (138 * SIZE_MULTIPLIER - RADIUS_CROW)
#define CROW_MIN_SPEED 200
#define CROW_MAX_SPEED 400

#define CROW_MIN_FLYING_FRAME 0
#define CROW_MAX_FLYING_FRAME 3
#define CROW_MIN_EATING_FRAME 4
#define CROW_MAX_EATING_FRAME 7
#define CROW_FRAME_TIME 0.05f


typedef struct Crow {
	Vector2 pos;
	f32 radius;
	f32 speed;
	u8 frame;
	f32 frame_timer;

	enum {
		FLYING,
		EATING,
	} state;
} Crow;

Crow* init_crow(Vector2 pos, f32 radius, f32 speed);
void update_crow(Crow* crow);
void draw_crow(Crow* crow, Texture_Manager* tex_manager);
Crow** init_crows(f32 radius, u16 crow_count);
void update_crows(Crow** crows, u16 crow_count);
void draw_crows(Crow** crows, u16 crow_count, Texture_Manager* tex_manager);
void add_to_crows(Crow*** crows, u16* crow_count, Vector2 pos);
void remove_from_crows(Crow*** crows, u16* crow_count, Crow* crow);

#endif