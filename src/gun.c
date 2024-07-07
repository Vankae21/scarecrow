#include "include/gun.h"
#include "include/vutils.h"
#include <math.h>
#include <stdio.h>
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

}

void update_bullets(Bullet** bullets, u16 bullet_count)
{

}

void draw_bullet(Bullet* bullet, Texture_Manager* tex_manager)
{
	Texture2D tex = tex_manager->tex_bullet;
	f32 degree = atan2f(bullet->dir.y, bullet->dir.x);
	DrawTexturePro(tex, (Rectangle){ 0, 0, tex.width, tex.height },
				    (Rectangle){ bullet->pos.x - bullet->radius, bullet->pos.y - bullet->radius, bullet->radius * 2, bullet->radius * 2 },
				    (Vector2){ bullet->radius, bullet->radius }, degree, WHITE);
	DrawCircleLinesV(bullet->pos, bullet->radius, RED);
}

void draw_bullets(Bullet** bullets, u16 bullet_count, Texture_Manager* tex_manager)
{
	for (int i = 0; i < bullet_count; i++) {
		draw_bullet(bullets[i], tex_manager);
	}
}

// GUN
Gun* init_gun(f32 x, f32 y, f32 width, f32 height, u16 bullet_count, f32 bullet_radius, f32 bullet_speed)
{
	Gun* gun = calloc(1, sizeof(Gun));

	gun->pos = (Vector2){ x, y };
	gun->hitbox = (Vector2){ width, height };
	gun->bullet_count = bullet_count;
	gun->bullets = init_bullets(bullet_radius, bullet_speed, bullet_count);
	gun->dir = (Vector2){0};
	gun->hit_point = (Vector2){ x + width, y };
	gun->rec = (Rectangle){ x, y, width, height };

	return gun;
}

void update_gun(Gun* gun)
{
	gun->dir = vec2_normalize((Vector2){ GetMouseX() - gun->pos.x, GetMouseY() - gun->pos.y });

	if (gun->dir.x <= 0.6f) {
		gun->dir.x = 0.6f;
		if (gun->dir.y >= 0.8f) {
			gun->dir.y = 0.8f;
		} else {
			gun->dir.y = -0.8f;
		}
	}

	gun->hit_point = (Vector2){ gun->pos.x + gun->hitbox.x * gun->dir.x, gun->pos.y + gun->hitbox.x * gun->dir.y };
	printf("x: %0.3f, y: %0.3f\n", gun->dir.x, gun->dir.y);
}

void draw_gun(Gun* gun, Texture_Manager* tex_manager)
{
	Texture2D tex = tex_manager->tex_gun;
	f32 degree = atan2f(gun->dir.y, gun->dir.x) * RAD2DEG;
	DrawTexturePro(tex, (Rectangle){ 0, 0, tex.width, tex.height }, gun->rec, (Vector2){0}, degree, WHITE);
	DrawRectangleLinesEx(gun->rec, 2, ORANGE);
	DrawCircleV(gun->hit_point, 4, WHITE);
}