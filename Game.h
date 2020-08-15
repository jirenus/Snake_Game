#pragma once

#include "Console.h"
#include "Snake.h"
#include "Board.h"
#include <ctime>
class Game
{
public:
	Game();
	~Game();

	void init();

	void handleEvents();
	void update();
	void render();
	void clean();

	bool isRunning();

private:
	bool running;
	
	Snake* snake;
	Board* board;
};

