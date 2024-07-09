#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/game.h"
#include "include/crow.h"
#include "include/gun.h"
#include "include/types.h"
#include "include/scarecrow.h"
#include "include/texture_manager.h"
#include "include/vutils.h"

u16 COUNT_CROW = 10;

Texture_Manager* tex_manager = (void*)0;
Scarecrow* scarecrow = (void*)0;
Crow** crows = (void*)0;


void init()
{
	srand(time(0));
	tex_manager = init_texture_manager();
	scarecrow = init_scarecrow(24, 300, tex_manager->tex_scarecrow.width * SIZE_MULTIPLIER, tex_manager->tex_scarecrow.height * SIZE_MULTIPLIER,
								tex_manager->tex_gun.width * SIZE_MULTIPLIER / 2);
	crows = init_crows(RADIUS_CROW, COUNT_CROW);
}

void update()
{
	update_scarecrow(scarecrow);

	update_crows(crows, COUNT_CROW);

	for (int i = 0; i < scarecrow->gun->bullet_count; i++) {
		if (!scarecrow->gun->bullets[i]->is_active) continue;
		Bullet* cur_bullet = scarecrow->gun->bullets[i];
		for (int j = 0; j < COUNT_CROW; j++) {
			Crow* cur_crow = crows[j];
			if (are_circles_colliding((Circle){ cur_bullet->pos, cur_bullet->radius }, (Circle){ cur_crow->pos, cur_crow->radius })) {
				deactivate_bullet(cur_bullet);
				remove_from_crows(&crows, &COUNT_CROW, cur_crow);
				break;
			}
		}
	}
}

void late_update()
{
	draw_background0(tex_manager);
	draw_scarecrow(scarecrow, tex_manager);

	char buffer[20];
	u8 ammo = 0;
	for (int i = 0; i < scarecrow->gun->bullet_count; i++) {
		if (!scarecrow->gun->bullets[i]->is_active) {
			ammo++;
		}
	}
	sprintf(buffer, "Ammo %d/%d", ammo, scarecrow->gun->bullet_count);
	DrawText(buffer, 0, 0, 32, BLACK);

	draw_crows(crows, COUNT_CROW, tex_manager);

	draw_background1(tex_manager);
}

void finish()
{

}