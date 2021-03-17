#include "game.h"

int events_init() {
	events = calloc(1, sizeof(events_t));

	if (!events) {
		return 1;
	}

	return 0;
}

void events_update() {
	if (events->ev.type == SDL_QUIT) {
		running = false;
	}

	if (direction_selected) {
		return;
	}

	switch (events->ev.type) {
		case SDL_KEYUP:
		switch (events->ev.key.keysym.sym) {
			case SDLK_r:
			if (dead) {
				fruits = 0;
				snake_destroy(&snake->head);
				snake = init_snake(SNAKE_INIT_X, SNAKE_INIT_Y);
				free(food);
				food = NULL;
				dead = false;
				SDL_SetWindowTitle(video->win, GAME_TITLE);
				LOG("Game reset\n");
			}
			break;
			case SDLK_RIGHT:
			if (snake->next_direction != DIR_LEFT) {
				snake->next_direction = DIR_RIGHT;
				direction_selected = true;
			}
			break;
			case SDLK_LEFT:
			if (snake->next_direction != DIR_RIGHT) {
				snake->next_direction = DIR_LEFT;
				direction_selected = true;
			}
			break;
			case SDLK_UP:
			if (snake->next_direction != DIR_DOWN) {
				snake->next_direction = DIR_UP;
				direction_selected = true;
			}
			break;
			case SDLK_DOWN:
			if (snake->next_direction != DIR_UP) {
				snake->next_direction = DIR_DOWN;
				direction_selected = true;
			}
			break;
			default:
			break;
		}

		LOGF("Next direction %d\n", snake->next_direction);
	}
}
