#include "log.h"
#include "enums.h"
#include "game.h"

int main(int argc, char* argv[]) {
	DBG("Game initializing");

	game_t* game = game_init();

	if (game_create(game) != GAME_STATUS_SUCCESS) {
		ERR("Failed to initialize snake game");
		return -1;
	}

	if (game_run(game) != GAME_STATUS_SUCCESS) {
		ERR("Fail while running snake game");
		return -1;
	}

	if (game_destroy(game) != GAME_STATUS_SUCCESS) {
		ERR("Failed to gracefully shutdown the game");
		return -1;
	}

	DBG("Game finished");
	return 0;
}
