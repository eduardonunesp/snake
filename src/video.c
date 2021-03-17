#include "game.h"

int video_init() {
	video = calloc(1, sizeof(video_t));

	if (!video) {
		return 1;
	}

	video->win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	video->renderer = SDL_CreateRenderer(video->win, -1, SDL_RENDERER_ACCELERATED);

	return 0;
}

void video_render() {
	SDL_SetRenderDrawColor(video->renderer, 0, 0, 0, 255);
	SDL_RenderClear(video->renderer);
	draw_food(video->renderer, food);
	draw_snake_body(video->renderer, snake->head);
	SDL_RenderPresent(video->renderer);
}

void video_quit() {
	SDL_DestroyRenderer(video->renderer);
	SDL_DestroyWindow(video->win);
	SDL_Quit();
}
