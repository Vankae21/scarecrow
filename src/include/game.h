#ifndef GAME_H
#define GAME_H

#include "texture_manager.h"
#include "types.h"

extern bool DEBUG;
extern Font font;

#define WIDTH 1024
#define HEIGHT 768
#define TITLE "Game"
#define FPS 60

#define SIZE_MULTIPLIER 4

#define MAX_CROP_HEALTH 100.0f

extern u16 COUNT_CROW;

void init();
void update();
void late_update();
void finish();

// NON-GAME FUNCTIONS
void draw_crop_health_bar(f32 crop_health, f32 max_crop_health, Texture_Manager* tex_manager);
void draw_timer(f32 timer);

#endif