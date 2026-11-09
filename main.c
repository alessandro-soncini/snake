#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#define WIDTH 20
#define HEIGHT 20

const int screen_width = 600;
const int screen_height = 600;

typedef struct {
	bool active;
	int x;
	int y;
} Snake;

typedef struct {
	int x;
	int y;
} Apple;

const float max_update_timer = 0.2;

int main(void) {
	InitWindow(screen_width, screen_height, "Snake");
	
	Snake snake[WIDTH * HEIGHT];
	memset(snake, 0, sizeof(Snake) * WIDTH * HEIGHT);
	size_t snake_len = 0;
	int dir_x = 1;
	int dir_y = 0;

	snake[0] = (Snake){
		.active = true,
		.x = WIDTH / 2,
		.y = HEIGHT / 2
	};
	snake_len++;

	Apple apple = (Apple){
		.x = GetRandomValue(0, WIDTH - 1),
		.y = GetRandomValue(0, HEIGHT - 1)
	};

	float update_timer = max_update_timer;

	while (!WindowShouldClose()) {

		size_t prev_dir_x = dir_x;
		size_t prev_dir_y = dir_y;

		if (IsKeyDown(KEY_RIGHT)) {
			dir_x = 1;
			dir_y = 0;
		} else if (IsKeyDown(KEY_LEFT)) {
			dir_x = -1;
			dir_y = 0;
		} else if (IsKeyDown(KEY_DOWN)) {
			dir_x = 0;
			dir_y = 1;
		} else if (IsKeyDown(KEY_UP)) {
			dir_x = 0;
			dir_y = -1;
		}

		if (snake[snake_len - 1].x - snake[snake_len - 2].x == dir_x && snake_len > 1) {
			dir_x = prev_dir_x;
			dir_y = prev_dir_y;
		}
		if (snake[snake_len - 1].y - snake[snake_len - 2].y == dir_y && snake_len > 1) {
			dir_x = prev_dir_x;
			dir_y = prev_dir_y;
		}

		update_timer -= GetFrameTime();

		if (update_timer <= 0) {
			snake[snake_len] = snake[snake_len-1];
			snake[snake_len].x += dir_x;
			snake[snake_len].y += dir_y;

			if (snake[snake_len].x == apple.x && snake[snake_len].y == apple.y) {
				snake_len++;

				bool touches_snake = true;
				apple.x = GetRandomValue(0, WIDTH - 1);
				apple.y = GetRandomValue(0, HEIGHT - 1);
				do {			
					touches_snake = false;
					for (size_t i = 0; i < snake_len + 1; ++i) {
						if (snake[i].x == apple.x && snake[i].y == apple.y) {
							touches_snake = true;
							apple.x = GetRandomValue(0, WIDTH - 1);
							apple.y = GetRandomValue(0, HEIGHT - 1);
						}
					}
				} while (touches_snake);
			} else {
				for (size_t i = 0; i < snake_len; ++i) {
					snake[i] = snake[i + 1];
				}
			}		

			for (size_t i = 0; i < snake_len - 1; ++i) {
				if (snake[i].x == snake[snake_len - 1].x && snake[i].y == snake[snake_len - 1].y) {				
					memset(snake, 0, sizeof(Snake) * WIDTH * HEIGHT);
					snake_len = 0;
					dir_x = 1;
					dir_y = 0;

					snake[0] = (Snake){
						.active = true,
						.x = WIDTH / 2,
						.y = HEIGHT / 2
					};

					snake_len++;

					bool touches_snake = true;
					apple.x = GetRandomValue(0, WIDTH - 1);
					apple.y = GetRandomValue(0, HEIGHT - 1);
					do {			
						touches_snake = false;
						for (size_t i = 0; i < snake_len + 1; ++i) {
							if (snake[i].x == apple.x && snake[i].y == apple.y) {
								touches_snake = true;
								apple.x = GetRandomValue(0, WIDTH - 1);
								apple.y = GetRandomValue(0, HEIGHT - 1);
							}
						}
					} while (touches_snake);
				}
			}

			if (snake[snake_len - 1].x < 0 || snake[snake_len - 1].x > WIDTH - 1 ||
				snake[snake_len - 1].y < 0 || snake[snake_len - 1].y > HEIGHT - 1) {
			
				memset(snake, 0, sizeof(Snake) * WIDTH * HEIGHT);
				snake_len = 0;
				dir_x = 1;
				dir_y = 0;

				snake[0] = (Snake){
					.active = true,
					.x = WIDTH / 2,
					.y = HEIGHT / 2
				};

				snake_len++;

				bool touches_snake = true;
				apple.x = GetRandomValue(0, WIDTH - 1);
				apple.y = GetRandomValue(0, HEIGHT - 1);
				do {			
					touches_snake = false;
					for (size_t i = 0; i < snake_len + 1; ++i) {
						if (snake[i].x == apple.x && snake[i].y == apple.y) {
							touches_snake = true;
							apple.x = GetRandomValue(0, WIDTH - 1);
							apple.y = GetRandomValue(0, HEIGHT - 1);
						}
					}
				} while (touches_snake);
			}

			update_timer = max_update_timer;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		for (size_t i = 0; i < snake_len; ++i) {
			if (!snake[i].active) continue;
			DrawRectangle(snake[i].x * screen_width / WIDTH, snake[i].y * screen_height / HEIGHT, screen_width / WIDTH, screen_height / HEIGHT, GREEN);
		}

		DrawRectangle(apple.x * screen_width / WIDTH, apple.y * screen_height / HEIGHT, screen_width / WIDTH, screen_height / HEIGHT, RED);
		
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
