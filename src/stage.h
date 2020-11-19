
#ifndef __STAGE_H__
#define __STAGE_H__

#include "snake.h"
#include "window.h"

typedef struct {
	window_t* window;
	snake_t* snake;
} stage_t;

stage_t* stage_init(window_t* window);

#endif // __STAGE_H__
