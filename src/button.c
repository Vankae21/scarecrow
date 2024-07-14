#include "include/button.h"
#include <raylib.h>
#include <stdlib.h>

Button* init_button(Vector2 size, Vector2 pos, const char* text, u8 font_size)
{
    Button* button = calloc(1, sizeof(Button));

    button->size = size;
    button->pos = pos;
    button->text = text;
    button->state = STILL;
    button->font_size = font_size;

    return button;
}

bool is_button_pressed(Button* button, Sound_Manager* sound_manager)
{
    if(GetMousePosition().x < button->pos.x ||
    GetMousePosition().x > button->pos.x + button->size.x ||
    GetMousePosition().y < button->pos.y ||
    GetMousePosition().y > button->pos.y + button->size.y ) {
        if(button->state != STILL) button->state = STILL;
        return false;
    } else if (button->state != HOLD) {
        button->state = OVER;
    }
    if(IsMouseButtonPressed(0) && button->state == OVER)
    {
        button->state = HOLD;
    } else if(IsMouseButtonReleased(0) && button->state == HOLD) {
        button->state = OVER;
        PlaySound(sound_manager->sound_click);
        return true;
    }
    return false;
}

void draw_button(Button* button)
{
    Color button_color;
    switch (button->state) {
        case STILL:
            button_color = WHITE;
            break;
        case OVER:
            button_color = LIGHTGRAY;
            break;
        case HOLD:
            button_color = GRAY;
            break;
        default:
            break;
    }

//    DrawRectangleV(button->pos, button->size, button_color);
    DrawRectangleRounded((Rectangle){ button->pos.x, button->pos.y, button->size.x, button->size.y }, 0.3f, 0, button_color);

    f32 spacing = 0;
    Vector2 text_measurement = MeasureTextEx(font, button->text, button->font_size, spacing);
    DrawTextEx(font, button->text,
               (Vector2){ button->pos.x + (button->size.x - text_measurement.x)/2, button->pos.y + (button->size.y - text_measurement.y)/2 },
               button->font_size, spacing, BLACK);
}