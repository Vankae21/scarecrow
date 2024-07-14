#include <raylib.h>
#include <string.h>
#include "include/game.h"

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--debug") == 0) {
			DEBUG = true;
		}
	}

	InitWindow(WIDTH, HEIGHT, TITLE);
	InitAudioDevice();
	SetTargetFPS(FPS);
	SetExitKey(0);

	init();

	Color bg_color = { 161, 187, 157, 255 };

	while (!WindowShouldClose()) {
		update();
		BeginDrawing();
		ClearBackground(bg_color);
		late_update();
		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
	finish();

	return 0;
}