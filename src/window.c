#include "window.h"
#include <assert.h>
#include "log.h"

window_t* window_init(int width, int height) {
	window_t* window = (window_t*)malloc(sizeof(window_t));

	assert(window);

	window->height = height;
	window->width = width;

	return window;
}

void window_create(window_t* window) {
	assert(window);
	assert(SDL_Init(SDL_INIT_EVERYTHING) == 0);

	SDL_Window* win = SDL_CreateWindow("Hello World", 0, 0, window->width, window->height, 0);
	assert(win);

	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	assert(renderer);

	window->win = win;
	window->renderer = renderer;
	window->running = 1;
}

void window_destroy(window_t* window) {
	assert(window);
	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->win);
	SDL_Quit();
}
