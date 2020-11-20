#include <stdbool.h>
#include <SDL2/SDL.h>

#define LOG(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SEGMENT_WIDTH 20
#define SEGMENT_HEIGHT 20

typedef enum {
	DIR_RIGHT,
	DIR_LEFT,
	DIR_DOWN,
	DIR_UP
} snake_dir_e;

typedef enum {
	EAT_NONE,
	EAT_FOOD,
	EAT_ITSELF,
} snake_eat_e;

typedef struct snake_body {
	int x, y;
	struct snake_body* next;
} snake_body_t;

typedef struct {
	snake_dir_e next_direction;
	snake_eat_e eat;
	snake_body_t* head;
} snake_t;

snake_t* init_snake(int grid_x, int grid_y) {
	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
	snake->next_direction = DIR_RIGHT;
	snake->eat = EAT_NONE;
	snake->head = (snake_body_t*)malloc(sizeof(snake_body_t));
	snake->head->x = grid_x;
	snake->head->y = grid_y;
	snake->head->next = NULL;
	return snake;
}

void snake_insert_head(snake_body_t** head, int grid_x, int grid_y) {
	snake_body_t* new_head = (snake_body_t*)malloc(sizeof(snake_body_t));
	new_head->x = grid_x;
	new_head->y = grid_y;
	new_head->next = *head;
	*head = new_head;
}

void snake_remove_tail(snake_body_t* head) {
	if (head->next == NULL) {
		free(head);
	}

	snake_body_t* current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}

	free(current->next);
	current->next = NULL;
}

void draw_snake_body(SDL_Renderer* renderer, snake_body_t* head) {
	snake_body_t* current = head;
	while (1) {
		SDL_Rect dst = { current->x * SEGMENT_WIDTH, current->y * SEGMENT_WIDTH, SEGMENT_WIDTH, SEGMENT_HEIGHT };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &dst);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		if (current->next == NULL) {
			break;
		}

		current = current->next;
	}
}

void update_snake(snake_t* snake) {
	int x, y = 0;

	switch (snake->next_direction)
	{
	case DIR_RIGHT:
		x = 1;
		y = 0;
		break;
	case DIR_LEFT:
		x = -1;
		y = 0;
		break;
	case DIR_UP:
		x = 0;
		y = -1;
		break;
	case DIR_DOWN:
		x = 0;
		y = 1;
		break;
	default:
		break;
	}

	snake_insert_head(&snake->head, snake->head->x + x, snake->head->y + y);

	switch (snake->eat) {
	case EAT_NONE:
		snake_remove_tail(snake->head);
		break;
	case EAT_ITSELF:
		exit(-1);
		break;
	case EAT_FOOD:
		break;
	}

	snake->eat = EAT_NONE;
}

int main(int argc, char* argv[]) {
	snake_t* snake = init_snake(10, 10);

	SDL_Window* win = SDL_CreateWindow("Hello World", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	bool running = true;
	unsigned int last_time = 0, current_time;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}

			switch (event.type) {
			case SDL_KEYUP:

				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					snake->next_direction = DIR_RIGHT;
					break;
				case SDLK_LEFT:
					snake->next_direction = DIR_LEFT;
					break;
				case SDLK_UP:
					snake->next_direction = DIR_UP;
					break;
				case SDLK_DOWN:
					snake->next_direction = DIR_DOWN;
					break;
				case SDLK_a:
					snake->eat = EAT_FOOD;
					break;
				default:
					break;
				}
			}
		}

		current_time = SDL_GetTicks();
		if (current_time > last_time) {
			update_snake(snake);
			last_time = current_time + 1000;
		}

		SDL_RenderClear(renderer);
		draw_snake_body(renderer, snake->head);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
