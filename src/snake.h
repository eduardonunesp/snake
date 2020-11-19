
#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "SDL2/SDL.h"
#include "enums.h"
#include "window.h"

typedef enum {
	SNAKE_MOVE_RIGHT,
	SNAKE_MOVE_LEFT,
	SNAKE_MOVE_DOWN,
	SNAKE_MOVE_UP,
} snake_direction_e;

typedef struct {
	SDL_Texture* texture;
	int x, y;
	int h, w;
	int size;
} snake_t;

snake_t* snake_init(int x, int y, int w, int h);

game_status_e snake_create(window_t* window, snake_t* snake);

void snake_move(snake_t* snake, snake_direction_e next_direction);

game_status_e snake_draw(window_t* window, snake_t* snake);

game_status_e snake_destroy(snake_t* snake);

#endif // __SNAKE_H__
