#include "game.h"

void draw_food(SDL_Renderer* renderer, segment_t* food)
{
	if (!food) {
		// Nothing to draw, skip it!
		return;
	}

	SDL_Rect dst = {food->x * SEGMENT_WIDTH, food->y * SEGMENT_WIDTH, SEGMENT_WIDTH, SEGMENT_HEIGHT};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &dst);
}

segment_t* add_food(snake_t* snake)
{
	int grid_width = SCREEN_WIDTH / SEGMENT_WIDTH;
	int grid_height = SCREEN_HEIGHT / SEGMENT_HEIGHT;
	int grid_x = -1;
	int grid_y = -1;

	while (true) {
		segment_t* current = snake->head;

		while (true) {
			int x = (rand() % (grid_width));
			int y = (rand() % (grid_height));

			if (current->x == x && snake->head->y == y) {
				break;
			}

			if (current->next == NULL) {
				grid_x = x;
				grid_y = y;
				break;
			}

			current = current->next;
		}

		if (grid_x != -1 && grid_y != -1) {
			break;
		}
	}

	segment_t* new_food = (segment_t*)malloc(sizeof(segment_t));
	new_food->seg_type = SEG_FOOD;
	new_food->x = grid_x;
	new_food->y = grid_y;
	LOGF("New food at %d-%d\n", new_food->x, new_food->y);
	return new_food;
}
