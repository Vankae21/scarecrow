#ifndef GAME_H
#define GAME_H

#include "types.h"

#define WIDTH 1024
#define HEIGHT 768
#define TITLE "Game"
#define FPS 60

#define SIZE_MULTIPLIER 4

extern u16 COUNT_CROW;

void init();
void update();
void late_update();
void finish();

#endif