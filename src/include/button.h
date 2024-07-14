#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"
#include "game.h"
#include "sound_manager.h"

typedef struct Button
{
    enum
    {
        STILL,
        OVER,
        HOLD
    } state;
    Vector2 size;
    Vector2 pos;
    const char* text;
    u8 font_size;
} Button;

Button* init_button(Vector2 size, Vector2 pos, const char* text, u8 font_size);
bool is_button_pressed(Button* button, Sound_Manager* sound_manager);
void draw_button(Button* button);

#endif