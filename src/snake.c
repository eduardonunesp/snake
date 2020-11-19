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

void snake_push_front(snake_t** head, int x, int y) {
	assert(head);

	snake_t* new_head = snake_init(x, y, 20, 20);

	new_head->next = (*head);
	(*head) = new_head;
}

void snake_remove_last(snake_t* head) {
	if (head->next == NULL) {
		free(head);
	}

	/* get to the second to last node in the list */
	snake_t* current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}

	/* now current points to the second to last item of the list, so let's remove current->next */
	free(current->next);
	current->next = NULL;
}

void snake_update(snake_t* snake) {
	assert(snake);

	int x, y = 0;
	switch (snake->current_direction)
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

	x = snake->x + (x * snake->w);
	y = snake->y + (y * snake->h);
	snake_push_front(&snake, x, y);
}

void snake_draw(window_t* window, snake_t* snake) {
	assert(window);
	assert(snake);

	snake_t* current = snake;
	while (current->next != NULL) {
		current = current->next;
		DBG("SD");
		// SDL_Rect dst = { current->x, current->y, current->w, current->h };
		// SDL_SetRenderDrawColor(window->renderer, 255, 255, 255, 255);
		// SDL_RenderDrawRect(window->renderer, &dst);
		// SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);

		// if (current->next == NULL) {
		// 	break;
		// }

	}
}

void snake_destroy(snake_t* snake) {
	assert(snake);
}
