#include "window.h"
#include "log.h"

window_t* window_init(int width, int height) {
	window_t* window = (window_t*)malloc(sizeof(window_t));

	if (!window) {
		DBG("Window can't be null !!!");
		return NULL;
	}

	window->height = height;
	window->width = width;

	return window;
}

game_status_e window_create(window_t* window) {
	if (!window) {
		DBG("Window can't be null !!!");
		return GAME_STATUS_INVALID_MEMORY;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		DBGF("Failed to init SDL %s", SDL_GetError());
		return GAME_STATUS_VIDEO_FAILED;
	}

	SDL_Window* win = SDL_CreateWindow("Hello World", 0, 0, window->width, window->height, 0);

	if (!win) {
		DBG("Failed to create SDL WIN");
		return GAME_STATUS_VIDEO_FAILED;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer) {
		DBG("Failed to create SDL Renderer");
		return GAME_STATUS_VIDEO_FAILED;
	}

	window->win = win;
	window->renderer = renderer;
	window->running = 1;

	return GAME_STATUS_SUCCESS;
}

game_status_e window_destroy(window_t* window) {
	if (!window) {
		DBG("Window can't be null !!!");
		return GAME_STATUS_INVALID_MEMORY;
	}

	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->win);
	SDL_Quit();

	return GAME_STATUS_SUCCESS;
}

