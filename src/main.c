#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define LOG(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)

#define GAME_TITLE "Snake"
#define GAME_TITLE_DEAD "Snake (DEAD)"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SEGMENT_WIDTH 40
#define SEGMENT_HEIGHT 40
#define SNAKE_INIT_X 5
#define SNAKE_INIT_Y 5

bool running = true;
bool dead = false;
bool direction_selected = false;
SDL_Window* win = NULL;
SDL_Renderer* renderer = NULL;

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
	EAT_WALL,
} snake_eat_e;

typedef enum {
	SEG_SNAKE,
	SEG_FOOD
} segment_e;

typedef struct segment {
	int x, y;
	segment_e seg_type;
	struct segment* next;
} segment_t;

typedef struct {
	snake_dir_e next_direction;
	snake_eat_e eat;
	segment_t* head;
} snake_t;

snake_t* init_snake(int grid_x, int grid_y) {
	snake_t* snake = (snake_t*)malloc(sizeof(snake_t));
	snake->next_direction = DIR_RIGHT;
	snake->eat = EAT_NONE;
	snake->head = (segment_t*)malloc(sizeof(segment_t));
	snake->head->seg_type = SEG_SNAKE;
	snake->head->x = grid_x;
	snake->head->y = grid_y;
	snake->head->next = NULL;
	return snake;
}

void snake_insert_head(segment_t** head, int grid_x, int grid_y) {
	segment_t* new_head = (segment_t*)malloc(sizeof(segment_t));
	new_head->seg_type = SEG_SNAKE;
	new_head->x = grid_x;
	new_head->y = grid_y;
	new_head->next = *head;
	*head = new_head;
}

void snake_remove_tail(segment_t* head) {
	if (head->next == NULL) {
		free(head);
	}

	segment_t* current = head;
	while (current->next->next != NULL) {
		current = current->next;
	}

	free(current->next);
	current->next = NULL;
}

void draw_snake_body(SDL_Renderer* renderer, segment_t* head) {
	segment_t* current = head;
	while (1) {
		SDL_Rect dst = { current->x * SEGMENT_WIDTH, current->y * SEGMENT_WIDTH, SEGMENT_WIDTH, SEGMENT_HEIGHT };

		if (dead) {
			SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		SDL_RenderFillRect(renderer, &dst);

		if (current->next == NULL) {
			break;
		}

		current = current->next;
	}
}

void draw_food(SDL_Renderer* renderer, segment_t* food) {
	if (!food) {
		// Nothing to draw, skip it!
		return;
	}

	SDL_Rect dst = { food->x * SEGMENT_WIDTH, food->y * SEGMENT_WIDTH, SEGMENT_WIDTH, SEGMENT_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &dst);
}

segment_t* add_food(snake_t* snake) {
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
	return new_food;
}

void update_snake(snake_t* snake, segment_t** food) {
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

	if (*food && snake->head->x == (*food)->x && snake->head->y == (*food)->y) {
		snake->eat = EAT_FOOD;
		free(*food);
		*food = NULL;
	}

	segment_t* current = snake->head;
	while (current->next != NULL) {
		current = current->next;

		if (snake->head->x == current->x && snake->head->y == current->y) {
			snake->eat = EAT_ITSELF;
		}
	}

	if (snake->head->x >= (SCREEN_WIDTH / SEGMENT_WIDTH) ||
		snake->head->y >= (SCREEN_HEIGHT / SEGMENT_HEIGHT) ||
		snake->head->x < 0 ||
		snake->head->y < 0) {
		snake->eat = EAT_WALL;
	}

	switch (snake->eat) {
	case EAT_NONE:
		snake_remove_tail(snake->head);
		break;
	case EAT_ITSELF:
	case EAT_WALL:
		dead = true;
		SDL_SetWindowTitle(win, GAME_TITLE_DEAD);
		break;
	case EAT_FOOD:
		// :D
		break;
	}

	snake->eat = EAT_NONE;
}

int main(int argc, char* argv[]) {
	srand(time(0));
	snake_t* snake = init_snake(SNAKE_INIT_X, SNAKE_INIT_Y);
	segment_t* food = NULL;

	win = SDL_CreateWindow(GAME_TITLE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	unsigned int last_time = 0, current_time;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}

			if (direction_selected) {
				break;
			}

			switch (event.type) {
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					if (snake->next_direction != DIR_LEFT) {
						snake->next_direction = DIR_RIGHT;
						direction_selected = true;
					}
					break;
				case SDLK_LEFT:
					if (snake->next_direction != DIR_RIGHT) {
						snake->next_direction = DIR_LEFT;
						direction_selected = true;
					}
					break;
				case SDLK_UP:
					if (snake->next_direction != DIR_DOWN) {
						snake->next_direction = DIR_UP;
						direction_selected = true;
					}
					break;
				case SDLK_DOWN:
					if (snake->next_direction != DIR_UP) {
						snake->next_direction = DIR_DOWN;
						direction_selected = true;
					}
					break;
				default:
					break;
				}
			}
		}

		current_time = SDL_GetTicks();
		if (current_time > last_time && !dead) {
			last_time = current_time + 500;
			update_snake(snake, &food);
			if (!food) food = add_food(snake);
			direction_selected = false;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		draw_snake_body(renderer, snake->head);
		draw_food(renderer, food);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
