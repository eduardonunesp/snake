
#ifndef __LIST_H__
#define __LIST_H__

#include "log.h"
#include "enums.h"
#include "stdlib.h"

typedef struct node {
	void* data;
	struct node* next;
} node_t;

game_status_e list_push(node_t* head, void* data);

#endif // __LIST_H__
