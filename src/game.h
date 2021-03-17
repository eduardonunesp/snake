#
#ifndef __GAME_H__
#define __GAME_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#ifdef _DEBUG
#define LOG(msg) printf(msg);
#define LOGF(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)
#else
#define LOG(fmt)
#define LOGF(fmt, ...)
#endif

#define GAME_TITLE "Snake"
#define GAME_TITLE_DEAD "Snake (DEAD)"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SEGMENT_WIDTH 40
#define SEGMENT_HEIGHT 40
#define SNAKE_INIT_X 5
#define SNAKE_INIT_Y 5

typedef struct game_s {
	unsigned int last_time;
	unsigned int current_time;
	bool running;
	int fruits;
	bool dead;
	bool direction_selected;
} game_t;

extern game_t *game;

int game_init();
void game_update();

typedef struct video_s {
	SDL_Window* win;
	SDL_Renderer* renderer;
} video_t;

extern video_t *video;

int video_init();
void video_render();
void video_quit();

typedef struct events_s {
	SDL_Event ev;
} events_t;

extern events_t *events;

int events_init();
void events_update();

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

extern snake_t *snake;
extern segment_t *food;

snake_t* init_snake(int grid_x, int grid_y);
void snake_insert_head(segment_t** head, int grid_x, int grid_y);
void snake_remove_tail(segment_t* head);
void snake_destroy(segment_t** head);
void draw_snake_body(SDL_Renderer* renderer, segment_t* head);
void update_snake(snake_t* snake, segment_t** food);
void draw_food(SDL_Renderer* renderer, segment_t* food);
segment_t* add_food(snake_t* snake);

#endif // __GAME_H__
