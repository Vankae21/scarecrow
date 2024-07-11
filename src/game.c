#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/game.h"
#include "include/button.h"
#include "include/crow.h"
#include "include/gun.h"
#include "include/types.h"
#include "include/scarecrow.h"
#include "include/texture_manager.h"
#include "include/vutils.h"

#if defined(_WIN32)
Platform PLATFORM = WINDOWS;
#elif defined(__APPLE__)
Platform PLATFORM = MACOS;
#elif defined(__linux__)
Platform PLATFORM = LINUX;
#else
Platform PLATFORM = UNKNOWN;
#endif

bool DEBUG = false;
bool PAUSED = false;

Game_State game_state = MENU;

f32 CROP_HEALTH = MAX_CROP_HEALTH;
f32 timer = .0f;
u16 COUNT_CROW = 6;

Texture_Manager* tex_manager = (void*)0;
Scarecrow* scarecrow = (void*)0;
Crow** crows = (void*)0;

// BUTTONS
Button* start_button = (void*)0, *exit_button = (void*)0, *github_button = (void*)0, *restart_button = (void*)0, *main_button = (void*)0;

// FONT
Font font;

void init()
{
	srand(time(0));
	tex_manager = init_texture_manager();
	scarecrow = init_scarecrow(24, 300, tex_manager->tex_scarecrow.width * SIZE_MULTIPLIER, tex_manager->tex_scarecrow.height * SIZE_MULTIPLIER,
								(f32)tex_manager->tex_gun.width * SIZE_MULTIPLIER / 2);
	crows = init_crows(RADIUS_CROW, HIT_RADIUS_CROW, COUNT_CROW);

	// BUTTONS
	f32 button_width = 292, button_height = 64;
	start_button = init_button((Vector2){ button_width, button_height }, (Vector2){ WIDTH/2 - 128, HEIGHT/2 - 32 - (button_height + 8) }, "start", 48);
	exit_button = init_button((Vector2){ button_width, button_height }, (Vector2){ WIDTH/2 - 128, HEIGHT/2 - 32 }, "exit", 48);
	github_button = init_button((Vector2){ 64, 64 }, (Vector2){ 8, HEIGHT - 8 - 64 }, "github", 12);

	// FONT
	font = LoadFontEx("assets/JOYSTIX_MONOSPACE.otf", 64, (void*)0, 300);
}

void update()
{
	if (game_state == MENU) {
		if (is_button_pressed(start_button)) {
			game_state = INGAME;
		} else if (is_button_pressed(exit_button)) {
			// exit
			exit(0);
		} else if (is_button_pressed(github_button)) {
			char command[64], *url = "https://github.com/Vankae21/scarecrow";
			switch (PLATFORM) {
				case LINUX:
					sprintf(command, "xdg-open %s &", url);
					break;
				case WINDOWS:
					sprintf(command, "start %s", url);
					break;
				default:
					break;
			}
			system(command);
		}
	}
	if (game_state != INGAME) return;

	// ACTIVATE DEBUG MODE
	if (IsKeyPressed(KEY_ENTER)) DEBUG = DEBUG ? false : true;

	update_scarecrow(scarecrow);

	update_crows(crows, COUNT_CROW, &CROP_HEALTH);

	for (int i = 0; i < scarecrow->gun->bullet_count; i++) {
		if (!scarecrow->gun->bullets[i]->is_active) continue;
		Bullet* cur_bullet = scarecrow->gun->bullets[i];
		for (int j = 0; j < COUNT_CROW; j++) {
			Crow* cur_crow = crows[j];
			if (are_circles_colliding((Circle){ cur_bullet->pos, cur_bullet->radius }, (Circle){ cur_crow->pos, cur_crow->hit_radius })) {
				deactivate_bullet(cur_bullet);
				remove_from_crows(&crows, &COUNT_CROW, cur_crow);
				break;
			}
		}
	}

	timer += GetFrameTime();
}

void late_update()
{
	draw_background0(tex_manager);
	draw_scarecrow(scarecrow, tex_manager);
	draw_crows(crows, COUNT_CROW, tex_manager);
	draw_background1(tex_manager);
	
	if (game_state == MENU) { 
		draw_button(start_button, tex_manager);
		draw_button(exit_button, tex_manager);
		draw_button(github_button, tex_manager);
	} else if (game_state == INGAME) {
		draw_crop_health_bar(CROP_HEALTH, MAX_CROP_HEALTH, tex_manager);
		draw_timer(timer);
	}
}

void finish()
{

}

//------------------------------------------------------------------------------------------------------
// NON-GAME FUNCS

void draw_crop_health_bar(f32 crop_health, f32 max_crop_health, Texture_Manager* tex_manager)
{
	Texture2D tex_hp0 = tex_manager->tex_hp0, tex_hp1 = tex_manager->tex_hp1;
	f32 r_width = 560;
	Rectangle max_bar = { (WIDTH - r_width)/2, 8, r_width, 64 };
	Rectangle cur_bar = { max_bar.x, max_bar.y, max_bar.width * crop_health / max_crop_health, max_bar.height };

	DrawRectangleRec(max_bar, RED);
	DrawRectangleRec(cur_bar, YELLOW);

	DrawTexturePro(tex_hp1, (Rectangle){ 0, 0, tex_hp0.width, tex_hp0.height}, max_bar, (Vector2){0}, 0, WHITE);
	DrawTexturePro(tex_hp0, (Rectangle){ 0, 0, tex_hp0.width * crop_health / max_crop_health, tex_hp0.height}, cur_bar, (Vector2){0}, 0, WHITE);

	if (DEBUG) {
		char buffer[32];
		sprintf(buffer, "max hp: %0.3f\ncurrent hp: %0.3f", max_crop_health, crop_health);
		f32 font_size = 12, spacing = 0;
		DrawTextEx(font, buffer, (Vector2){ 16, 16 }, font_size, spacing, BLACK);
	}
}

void draw_timer(f32 timer)
{
	char buffer[32];
	sprintf(buffer, "Time passed:%d", (u32)timer);
	if (DEBUG) {
		sprintf(buffer, "Time passed:%0.3f", timer);
	}
	DrawTextEx(font, buffer, (Vector2){ 8, 80 }, 32, 0, BLACK);
}