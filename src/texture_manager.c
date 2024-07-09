#include "include/texture_manager.h"
#include "include/game.h"
#include <stdlib.h>

Texture_Manager* init_texture_manager()
{
	Texture_Manager* texture_manager = calloc(1, sizeof(Texture_Manager));

	texture_manager->tex_scarecrow = LoadTexture("assets/scarecrow.png");
	texture_manager->tex_gun = LoadTexture("assets/gun.png");
	texture_manager->tex_bullet = LoadTexture("assets/bullet.png");
	texture_manager->tex_crow = LoadTexture("assets/crow.png");
	texture_manager->tex_background0 = LoadTexture("assets/background0.png");
	texture_manager->tex_background1 = LoadTexture("assets/background1.png");

	return texture_manager;
}

void draw_background0(Texture_Manager* tex_manager)
{
	Texture2D tex = tex_manager->tex_background0;
//	DrawTexturePro(tex, (Rectangle) { 0, 0, tex.width, tex.height }, (Rectangle){ 0, 0, WIDTH, HEIGHT }, (Vector2){0}, 0, WHITE);
	DrawTextureEx(tex, (Vector2){0}, 0, SIZE_MULTIPLIER, WHITE);
}

void draw_background1(Texture_Manager* tex_manager)
{
	Texture2D tex = tex_manager->tex_background1;
//	DrawTexturePro(tex, (Rectangle) { 0, 0, tex.width, tex.height }, (Rectangle){ 0, 0, WIDTH, HEIGHT }, (Vector2){0}, 0, WHITE);
	DrawTextureEx(tex, (Vector2){0}, 0, SIZE_MULTIPLIER, WHITE);
}