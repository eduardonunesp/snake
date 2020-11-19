#include "list.h"
#include <assert.h>

game_status_e list_push(node_t* head, void* data) {
	assert(head);
	assert(data);

	node_t* current = head;

	while (current->next != NULL) {
		current = current->next;
	}

	/* now we can add a new variable */
	current->next = (node_t*)malloc(sizeof(node_t));
	assert(current->next);

	current->next->data = data;
	current->next->next = NULL;

	return GAME_STATUS_SUCCESS;
}

