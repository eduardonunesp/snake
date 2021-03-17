#include "game.h"

int main(int argc, char* argv[]) {
	srand(time(0));
	snake = init_snake(SNAKE_INIT_X, SNAKE_INIT_Y);

	if (game_init() > 0) {
		fprintf(stderr, "Failed to start game\n");
		exit(1);
	}

	if (video_init() > 0) {
		fprintf(stderr, "Failed to start video\n");
		exit(1);
	}

	if (events_init() > 0) {
		fprintf(stderr, "Failed to start events\n");
		exit(1);
	}

	LOG("Game start\n");

	while (game->running) {
		while (SDL_PollEvent(&events->ev)) {
			events_update();
		}

		game_update();
		video_render();
	}

	video_quit();

	LOG("Game end, bye!\n");

	return 0;
}
