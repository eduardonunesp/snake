#include "game.h"

int main(int argc, char* argv[]) {
	srand(time(0));
	snake = init_snake(SNAKE_INIT_X, SNAKE_INIT_Y);

	if (video_init() > 0) {
		fprintf(stderr, "Failed to start video\n");
		exit(0);
	}

	if (events_init() > 0) {
		fprintf(stderr, "Failed to start events\n");
		exit(0);
	}

	LOG("Game start\n");

	unsigned int last_time = 0;
	unsigned int current_time = 0;

	while (running) {
		while (SDL_PollEvent(&events->ev)) {
			events_update();
		}

		current_time = SDL_GetTicks();
		if (current_time > last_time && !dead) {
			last_time = current_time + (500 - (fruits * 10));
			update_snake(snake, &food);
			if (!food) {
				fruits++;
				food = add_food(snake);
			}

			direction_selected = false;
		}

		video_render();
	}

	video_quit();

	LOG("Game end, bye!\n");

	return 0;
}
