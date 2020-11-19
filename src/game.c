#include "game.h"
#include <assert.h>
#include "log.h"

#define TICK_INTERVAL 10
static Uint32 next_time;

Uint32 time_left(void) {
	Uint32 now;

	now = SDL_GetTicks();
	if (next_time <= now)
		return 0;
	else
		return next_time - now;
}

game_t* game_init() {
	game_t* game = (game_t*)malloc(sizeof(game_t));

	if (!game) {
		return NULL;
	}

	game->window = NULL;
	game->stage = NULL;
	game->snake = NULL;

	return game;
}

game_status_e game_create(game_t* game) {
	CHECKER_INIT(GAME_STATUS_SUCCESS);

	window_t* window = window_init(640, 480);

	if (!window) {
		return GAME_STATUS_MEMORY_ALLOC_FAILED;
	}

	CHECKER_RUN(window_create(window));

	game->window = window;

	snake_t* snake = snake_init(0, 0, 20, 20);

	if (!snake) {
		return GAME_STATUS_MEMORY_ALLOC_FAILED;
	}

	CHECKER_RUN(snake_create(window, snake));

	game->snake = snake;

	CHECKER_END();
}

game_status_e game_update(game_t* game) {
	assert(game);

	snake_move(game->snake, SNAKE_MOVE_RIGHT);

	return GAME_STATUS_SUCCESS;
}

game_status_e game_run(game_t* game) {
	assert(game);

	CHECKER_INIT(GAME_STATUS_SUCCESS);

	unsigned int lastTime = 0, currentTime;
	while (game->window->running) {

		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				game->window->running = 0;
			}
		}

		SDL_RenderClear(game->window->renderer);
		snake_draw(game->window, game->snake);
		SDL_RenderPresent(game->window->renderer);

		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1000) {
			game_update(game);
			lastTime = currentTime;
		}
	}

	CHECKER_END();
}

game_status_e game_destroy(game_t* game) {
	CHECKER_INIT(GAME_STATUS_SUCCESS);
	CHECKER_RUN(window_destroy(game->window));
	CHECKER_RUN(snake_destroy(game->snake));
	CHECKER_END();
}
