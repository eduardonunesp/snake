#include "game.h"

game_t *game = NULL;
video_t *video = NULL;
events_t *events = NULL;
snake_t *snake = NULL;
segment_t *food = NULL;

int game_init() {
	game = calloc(1, sizeof(game_t));

	if (!game) {
		return 1;
	}

	game->last_time = 0;
	game->current_time = 0;
	game->running = true;
	game->fruits = 0;
	game->dead = false;
	game->direction_selected = false;

	return 0;
}

void game_update() {
	game->current_time = SDL_GetTicks();
	if (game->current_time > game->last_time && !game->dead) {
		game->last_time = game->current_time + (500 - (game->fruits * 10));
		update_snake(snake, &food);
		if (!food) {
			game->fruits++;
			food = add_food(snake);
		}

		game->direction_selected = false;
	}
}
