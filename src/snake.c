#include "game.h"

snake_t* init_snake(int grid_x, int grid_y)
{
	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
	snake->next_direction = DIR_RIGHT;
	snake->eat = EAT_NONE;
	snake->head = (segment_t*)malloc(sizeof(segment_t));
	snake->head->seg_type = SEG_SNAKE;
	snake->head->x = grid_x;
	snake->head->y = grid_y;
	snake->head->next = NULL;
	return snake;
}

void snake_insert_head(segment_t** head, int grid_x, int grid_y)
{
	segment_t* new_head = (segment_t*)malloc(sizeof(segment_t));
	new_head->seg_type = SEG_SNAKE;
	new_head->x = grid_x;
	new_head->y = grid_y;
	new_head->next = *head;
	*head = new_head;
	LOGF("Add segment %p\n", new_head);
}

void snake_remove_tail(segment_t* head)
{
	if (head->next == NULL) {
		LOGF("Remove segment %p\n", head);
		free(head);
	}

	segment_t* current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}

	LOGF("Remove segment %p\n", current->next);

	free(current->next);
	current->next = NULL;
}

void snake_destroy(segment_t** head)
{
	segment_t* current = *head;
	segment_t* next;

	while (current != NULL) {
		LOGF("Destroy and remove segment %p\n", current);
		next = current->next;
		free(current);
		current = next;
	}

	*head = NULL;
}

void draw_snake_body(SDL_Renderer* renderer, segment_t* head)
{
	segment_t* current = head;
	while (1) {
		SDL_Rect dst = {current->x * SEGMENT_WIDTH, current->y * SEGMENT_WIDTH, SEGMENT_WIDTH, SEGMENT_HEIGHT};

		if (game->dead) {
			SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
		} 		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		SDL_RenderFillRect(renderer, &dst);

		if (current->next == NULL) {
			break;
		}

		current = current->next;
	}
}

void update_snake(snake_t* snake, segment_t** food)
{
	int x, y = 0;

	switch (snake->next_direction) 	{
		case DIR_RIGHT:
		x = 1;
		y = 0;
		break;
		case DIR_LEFT:
		x = -1;
		y = 0;
		break;
		case DIR_UP:
		x = 0;
		y = -1;
		break;
		case DIR_DOWN:
		x = 0;
		y = 1;
		break;
		default:
		break;
	}

	snake_insert_head(&snake->head, snake->head->x + x, snake->head->y + y);

	if (*food && snake->head->x == (*food)->x && snake->head->y == (*food)->y) {
		snake->eat = EAT_FOOD;
		free(*food);
		*food = NULL;
	}

	segment_t* current = snake->head;
	while (current->next != NULL) {
		current = current->next;

		if (snake->head->x == current->x && snake->head->y == current->y) {
			snake->eat = EAT_ITSELF;
		}
	}

	if (snake->head->x >= (SCREEN_WIDTH / SEGMENT_WIDTH) ||
		snake->head->y >= (SCREEN_HEIGHT / SEGMENT_HEIGHT) ||
		snake->head->x < 0 ||
		snake->head->y < 0) {
		snake->eat = EAT_WALL;
	}

	switch (snake->eat) {
		case EAT_NONE:
		snake_remove_tail(snake->head);
		break;
		case EAT_ITSELF:
		case EAT_WALL:
		game->dead = true;
		SDL_SetWindowTitle(video->win, GAME_TITLE_DEAD);
		break;
		case EAT_FOOD:
		// :D
		break;
	}

	snake->eat = EAT_NONE;
}
