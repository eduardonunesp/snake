#include "game.h"
#include <assert.h>
#include "log.h"

game_t* game_init() {
	game_t* game = (game_t*)malloc(sizeof(game_t));
	assert(game);

	game->window = NULL;
	game->snake = NULL;
	game->next_direction = SNAKE_MOVE_RIGHT;

	return game;
}

void game_create(game_t* game) {
	window_t* window = window_init(640, 480);
	window_create(window);
	game->window = window;
	game->snake = snake_init(10, 10, 20, 20);
}

void game_run(game_t* game) {
	assert(game);

	unsigned int last_time = 0, current_time;
	while (game->window->running) {

		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				game->window->running = 0;
			}

			switch (e.type) {
			case SDL_KEYUP:

				switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
					game->next_direction = SNAKE_MOVE_RIGHT;
					break;
				case SDLK_LEFT:
					game->next_direction = SNAKE_MOVE_LEFT;
					break;
				case SDLK_UP:
					game->next_direction = SNAKE_MOVE_UP;
					break;
				case SDLK_DOWN:
					game->next_direction = SNAKE_MOVE_DOWN;
					break;
				case SDLK_a:
					// snake_push_front(game->snake);
					break;
				default:
					break;
				}

				break;
			default:
				break;
			}
		}

		SDL_RenderClear(game->window->renderer);
		snake_draw(game->window, game->snake);
		SDL_RenderPresent(game->window->renderer);

		current_time = SDL_GetTicks();
		if (current_time > last_time + 1000) {
			game->snake->current_direction = game->next_direction;
			snake_update(game->snake);
			last_time = current_time;
		}
	}
}

void game_destroy(game_t* game) {
	assert(game);
	window_destroy(game->window);
	snake_destroy(game->snake);
}
