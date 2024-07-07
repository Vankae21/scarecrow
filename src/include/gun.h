#ifndef GUN_H
#define GUN_H

#include <raylib.h>
#include "texture_manager.h"
#include "types.h"

typedef struct Bullet {
	Vector2 pos;
	Vector2 dir;
	f32 radius;
	f32 speed;
	bool is_active;
} Bullet;

typedef struct Gun {
	Vector2 pos;
	Vector2 hitbox;
	Vector2 dir;
	Rectangle rec;
	Vector2 hit_point;
	Bullet** bullets;
	u16 bullet_count;
} Gun;

Bullet* init_bullet(f32 radius, f32 speed);
Bullet** init_bullets(f32 radius, f32 speed, u16 bullet_count);
void update_bullet(Bullet* bullet);
void update_bullets(Bullet** bullets, u16 bullet_count);
void draw_bullet(Bullet* bullet, Texture_Manager* tex_manager);
void draw_bullets(Bullet** bullets, u16 bullet_count, Texture_Manager* tex_manager);

Gun* init_gun(f32 x, f32 y, f32 width, f32 height, u16 bullet_count, f32 bullet_radius, f32 bullet_speed);
void update_gun(Gun* gun);
void draw_gun(Gun* gun, Texture_Manager* tex_manager);

#endif