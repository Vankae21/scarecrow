#ifndef GUN_H
#define GUN_H

#include <raylib.h>
#include "sound_manager.h"
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
	f32 radius;
	Vector2 dir;
	Vector2 hit_point;
	Bullet** bullets;
	u16 bullet_count;
	f32 shot_break;
	f32 shot_break_elapsed;
} Gun;

Bullet* init_bullet(f32 radius, f32 speed);
Bullet** init_bullets(f32 radius, f32 speed, u16 bullet_count);
void update_bullet(Bullet* bullet);
void update_bullets(Bullet** bullets, u16 bullet_count);
void draw_bullet(Bullet* bullet, Texture_Manager* tex_manager);
void draw_bullets(Bullet** bullets, u16 bullet_count, Texture_Manager* tex_manager);
void deactivate_bullet(Bullet* bullet);

Gun* init_gun(f32 x, f32 y, f32 radius, u16 bullet_count, f32 bullet_radius, f32 bullet_speed);
void update_gun(Gun* gun, Sound_Manager* sound_manager);
void draw_gun(Gun* gun, Texture_Manager* tex_manager);
void shoot_gun(Gun* gun, Sound_Manager* sound_manager);
void deactivate_gun_bullets(Gun* gun);

#endif