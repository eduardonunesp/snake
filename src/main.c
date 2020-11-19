#include <assert.h>
#include "log.h"
#include "game.h"

int main(int argc, char* argv[]) {
	DBG("Game initializing");

	game_t* game = game_init();
	game_create(game);
	game_run(game);
	game_destroy(game);

	DBG("Game finished");
	return 0;
}
