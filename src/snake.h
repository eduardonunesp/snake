
#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "SDL2/SDL.h"
#include "window.h"

typedef enum {
	SNAKE_MOVE_RIGHT,
	SNAKE_MOVE_LEFT,
	SNAKE_MOVE_DOWN,
	SNAKE_MOVE_UP,
} snake_direction_e;

typedef struct snake {
	SDL_Window* window;
	int x, y;
	int h, w;
	snake_direction_e current_direction;
	struct snake* next;
} snake_t;

snake_t* snake_init(int x, int y, int w, int h);

void snake_push_front(snake_t** head, int x, int y);

void snake_remove_last(snake_t* head);

void snake_update(snake_t* snake);

void snake_draw(window_t* window, snake_t* snake);

void snake_destroy(snake_t* snake);

#endif // __SNAKE_H__
