#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "enums.h"
#include <SDL2/SDL.h>

typedef struct {
	SDL_Window* win;
	SDL_Renderer* renderer;
	int width, height;
	int running;
} window_t;

window_t* window_init(int width, int height);

game_status_e window_create(window_t* window);

game_status_e window_destroy(window_t* window);

#endif // __WINDOW_H__
