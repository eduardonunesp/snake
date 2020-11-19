#ifndef __GAME_H__
#define __GAME_H__

#include "enums.h"
#include "window.h"
#include "stage.h"
#include "snake.h"

typedef struct {
	window_t* window;
	stage_t* stage;
	snake_t* snake;
} game_t;

game_t* game_init();

game_status_e game_create(game_t* game);

game_status_e game_update(game_t* game);

game_status_e game_run(game_t* game);

game_status_e game_destroy(game_t* game);

#endif // __GAME_H__
