#include <stdlib.h>
#include "raylib.h"

#define WIDTH 20
#define HEIGHT 20

const int screen_width = 600;
const int screen_height = 600;

int main(void) {
	InitWindow(screen_width, screen_height, "Snake");

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(RAYWHITE);

		for (size_t x = 0; x < WIDTH; ++x) {
			DrawLine(screen_width / WIDTH * x, 0, screen_width /  WIDTH * x, screen_height, BLACK);
		}

		for (size_t y = 0; y < HEIGHT; ++y) {
			DrawLine(0, screen_height / HEIGHT * y, screen_height, screen_height / HEIGHT * y, BLACK);
		}

		DrawFPS(8, 8);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}
