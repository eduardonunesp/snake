#include "stage.h"

stage_t* stage_init(window_t* window) {
	stage_t* stage = (stage_t*)malloc(sizeof(stage_t));

	if (!stage) {
		return NULL;
	}

	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));

	if (!snake) {
		return NULL;
	}

	stage->snake = snake;
	stage->window = window;

	return stage;
}
