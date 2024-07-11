#include "include/gun.h"
#include "include/game.h"
#include "include/vutils.h"
#include <math.h>
#include <raylib.h>
#include <stdlib.h>

// BULLET
Bullet* init_bullet(f32 radius, f32 speed)
{
	Bullet* bullet = calloc(1, sizeof(Bullet));

	bullet->is_active = false;
	bullet->pos = (Vector2){0};
	bullet->radius = radius;
	bullet->speed = speed;

	return bullet;
}

Bullet** init_bullets(f32 radius, f32 speed, u16 bullet_count)
{
	Bullet** bullets = calloc(bullet_count, sizeof(Bullet*));
	
	for (int i = 0; i < bullet_count; i++) {
		bullets[i] = init_bullet(radius, speed);
	}

	return bullets;
}

void update_bullet(Bullet* bullet)
{
	if (!bullet->is_active) return;

	bullet->pos.x += bullet->speed * bullet->dir.x * GetFrameTime();
	bullet->pos.y += bullet->speed * bullet->dir.y * GetFrameTime();

	if (bullet->pos.x - bullet->radius > WIDTH || bullet->pos.y - bullet->radius > HEIGHT || bullet->pos.y + bullet->radius < 0) {
		bullet->is_active = false;
	}
}

void update_bullets(Bullet** bullets, u16 bullet_count)
{
	for (int i = 0; i < bullet_count; i++) {
		update_bullet(bullets[i]);
	}
}

void draw_bullet(Bullet* bullet, Texture_Manager* tex_manager)
{
	if (!bullet->is_active) return;
	Texture2D tex = tex_manager->tex_bullet;
	f32 degree = atan2f(bullet->dir.y, bullet->dir.x) * RAD2DEG;
	DrawTexturePro(tex, (Rectangle){ 0, 0, tex.width, tex.height },
				    (Rectangle){ bullet->pos.x, bullet->pos.y, bullet->radius * 2, bullet->radius * 2 },
				    (Vector2){ bullet->radius, bullet->radius }, degree, WHITE);
	if (DEBUG)
		DrawCircleLinesV(bullet->pos, bullet->radius, RED);
}

void draw_bullets(Bullet** bullets, u16 bullet_count, Texture_Manager* tex_manager)
{
	for (int i = 0; i < bullet_count; i++) {
		draw_bullet(bullets[i], tex_manager);
	}
}

void deactivate_bullet(Bullet* bullet)
{
	bullet->is_active = false;
}

// GUN
Gun* init_gun(f32 x, f32 y, f32 radius, u16 bullet_count, f32 bullet_radius, f32 bullet_speed)
{
	Gun* gun = calloc(1, sizeof(Gun));

	gun->pos = (Vector2){ x, y };
	gun->radius = radius;
	gun->bullet_count = bullet_count;
	gun->bullets = init_bullets(bullet_radius, bullet_speed, bullet_count);
	gun->dir = (Vector2){0};
	gun->hit_point = (Vector2){0};
	gun->shot_break = 0.1f;
	gun->shot_break_elapsed = gun->shot_break;

	return gun;
}

void update_gun(Gun* gun)
{
	gun->dir = vec2_normalize((Vector2){ GetMouseX() - gun->pos.x, GetMouseY() - gun->pos.y });

	if (gun->dir.x <= 0.6f) {
		gun->dir.x = 0.6f;
		if (gun->dir.y >= 0) {
			gun->dir.y = 0.8f;
		} else {
			gun->dir.y = -0.8f;
		}
	}

	gun->hit_point = (Vector2){ gun->pos.x + gun->radius * gun->dir.x, gun->pos.y + gun->radius * gun->dir.y };

	gun->shot_break_elapsed += GetFrameTime();
	if (IsMouseButtonPressed(0) && gun->shot_break_elapsed >= gun->shot_break) {
		shoot_gun(gun);
	}

	update_bullets(gun->bullets, gun->bullet_count);
}

void draw_gun(Gun* gun, Texture_Manager* tex_manager)
{
	Texture2D tex = tex_manager->tex_gun;
	f32 degree = atan2f(gun->dir.y, gun->dir.x) * RAD2DEG;
	DrawTexturePro(tex, (Rectangle){ 0, 0, tex.width, tex.height },
				   (Rectangle){ gun->pos.x, gun->pos.y, gun->radius * 2, gun->radius * 2 },
				   (Vector2){ gun->radius, gun->radius }, degree, WHITE);

	if (DEBUG) {
		DrawCircleV(gun->hit_point, 4, WHITE);
		DrawCircleLinesV(gun->pos, gun->radius, ORANGE);
	}

	draw_bullets(gun->bullets, gun->bullet_count, tex_manager);
}

void shoot_gun(Gun* gun)
{
	if (gun->shot_break_elapsed < gun->shot_break) return;

	for (int i = 0; i < gun->bullet_count; i++) {
		if (!gun->bullets[i]->is_active) {
			Bullet* bullet = gun->bullets[i];

			bullet->is_active = true;
			bullet->dir = gun->dir;
			bullet->pos = gun->hit_point;

			gun->shot_break_elapsed = 0;
			return;
		}
	}
}