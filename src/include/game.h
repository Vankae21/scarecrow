#ifndef GAME_H
#define GAME_H

#include "texture_manager.h"
#include "types.h"

extern bool DEBUG;
extern Font font;

#define WIDTH 1024
#define HEIGHT 768
#define TITLE "Scare the Crows"
#define FPS 60

#define SIZE_MULTIPLIER 4

#define MAX_CROP_HEALTH 100.0f

extern u16 COUNT_CROW;

typedef enum {
	MENU,
	INGAME,
	PAUSE,
	LOSE,
} Game_State;

typedef enum {
	LINUX,
	WINDOWS,
	MACOS,
	UNKNOWN,
} Platform;

void init();
void update();
void late_update();
void finish();

// NON-GAME FUNCTIONS
void draw_crop_health_bar(f32 crop_health, f32 max_crop_health, Texture_Manager* tex_manager);
void draw_timer(f32 timer);
void draw_cursor(Texture_Manager* tex_manager);

// GAMEPLAY FUNCTIONS
void restart_game(u16 crow_count);
void main_menu();
void lose();
void spawn_crows();

#endif 