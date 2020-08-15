#include "Snake.h"
#include "Console.h"
#include "Board.h"
#include "Game.h"

#include <time.h>

int main()
{
	Game *game = new Game();

	game->init();
	while (game->isRunning()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	return 0;
}