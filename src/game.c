#include "game.h"

bool running = true;
int fruits = 0;
bool dead = false;
bool direction_selected = false;

video_t *video = NULL;
events_t *events = NULL;
snake_t *snake = NULL;
segment_t *food = NULL;
