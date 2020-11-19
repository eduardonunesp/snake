#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>

typedef struct {
	SDL_Window* win;
	SDL_Renderer* renderer;
	int width, height;
	int running;
} window_t;

window_t* window_init(int width, int height);

void window_create(window_t* window);

void window_destroy(window_t* window);

#endif // __WINDOW_H__
