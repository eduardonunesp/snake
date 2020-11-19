#include "snake.h"
#include "log.h"
#include <assert.h>
#include <SDL2/SDL_image.h>

snake_t* snake_init(int x, int y, int w, int h) {
	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));

	assert(snake);

	snake->w = w;
	snake->h = h;

	snake->x = x * w;
	snake->y = y * h;
	snake->next = NULL;

	snake->current_direction = SNAKE_MOVE_RIGHT;

	return snake;
}

game_status_e snake_create(window_t* window, snake_t* snake) {
	assert(window);
	assert(snake);

	SDL_Surface* surface = IMG_Load("resources/images/block.png");

	if (!surface) {
		return GAME_STATUS_FAILE_LOAD_SURFACE;
	}

	snake->texture = SDL_CreateTextureFromSurface(window->renderer, surface);

	if (!snake->texture) {
		return GAME_STATUS_FAILE_LOAD_TEXTURE;
	}

	SDL_FreeSurface(surface);

	return GAME_STATUS_SUCCESS;
}

game_status_e snake_push(window_t* window, snake_t* head) {
	assert(window);
	assert(head);

	CHECKER_INIT(GAME_STATUS_SUCCESS);

	snake_t* current = head;

	while (current->next != NULL) {
		current = current->next;
	}

	/* now we can add a new variable */
	current->next = snake_init(0, 0, 20, 20);
	assert(current->next);

	CHECKER_RUN(snake_create(window, current->next));

	current->next->next = NULL;

	CHECKER_END();
}

game_status_e snake_draw(window_t* window, snake_t* snake) {
	assert(window);
	assert(snake);

	SDL_Rect src = { 0, 0, snake->w, snake->h };
	SDL_Rect dst = { snake->x, snake->y, snake->w, snake->h };

	SDL_RenderCopy(window->renderer, snake->texture, &src, &dst);

	snake_t* current = snake;

	while (current->next != NULL) {
		current = current->next;
		SDL_Rect src = { 0, 0, current->w, current->h };
		SDL_Rect dst = { current->x, current->y, current->w, current->h };
		SDL_RenderCopy(window->renderer, current->texture, &src, &dst);
	}

	return GAME_STATUS_SUCCESS;
}

void snake_move(snake_t* snake, snake_direction_e next_direction) {
	assert(snake);

	int x, y = 0;

	switch (next_direction)
	{
	case SNAKE_MOVE_RIGHT:
		x = 1;
		y = 0;
		break;
	case SNAKE_MOVE_LEFT:
		x = -1;
		y = 0;
		break;
	case SNAKE_MOVE_UP:
		x = 0;
		y = -1;
		break;
	case SNAKE_MOVE_DOWN:
		x = 0;
		y = 1;
		break;
	default:
		break;
	}

	snake->x = snake->x + (x * snake->w);
	snake->y = snake->y + (y * snake->h);

	snake_t* current = snake;
	snake_t* prev = current;

	while (current->next != NULL) {
		current = current->next;

		int x, y = 0;

		switch (prev->current_direction)
		{
		case SNAKE_MOVE_RIGHT:
			x = 1;
			y = 0;
			break;
		case SNAKE_MOVE_LEFT:
			x = -1;
			y = 0;
			break;
		case SNAKE_MOVE_UP:
			x = 0;
			y = -1;
			break;
		case SNAKE_MOVE_DOWN:
			x = 0;
			y = 1;
			break;
		default:
			break;
		}

		current->x = prev->x + (x * 20);
		current->y = prev->y + (y * 20);

		if (current->next) {
			current->next->current_direction = next_direction;
		}

		prev = current;
	}
}

game_status_e snake_destroy(snake_t* snake) {
	assert(snake);
	SDL_DestroyTexture(snake->texture);
	return GAME_STATUS_SUCCESS;
}
