#ifndef SCARECROW_H
#define SCARECROW_H

#include <raylib.h>
#include "gun.h"
#include "texture_manager.h"
#include "types.h"

typedef struct Scarecrow {
	Vector2 pos;
	Vector2 hitbox;
	Rectangle rec;
	Gun* gun;
} Scarecrow;

Scarecrow* init_scarecrow(f32 x, f32 y, f32 width, f32 height, f32 gun_radius);
void update_scarecrow(Scarecrow* scarecrow);
void draw_scarecrow(Scarecrow* scarecrow, Texture_Manager* tex_manager);

#endif