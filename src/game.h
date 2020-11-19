#ifndef __GAME_H__
#define __GAME_H__

#include "window.h"
#include "snake.h"

typedef struct {
	window_t* window;
	snake_t* snake;
	snake_direction_e next_direction;
} game_t;

game_t* game_init();

void game_create(game_t* game);

void game_run(game_t* game);

void game_destroy(game_t* game);

#endif // __GAME_H__
