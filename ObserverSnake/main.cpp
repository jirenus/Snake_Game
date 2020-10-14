#include "Game.h"

#include <iostream>
#include <ctime>
#include <conio.h>

int main() {
	// Create time seed
	srand(static_cast<unsigned int>(time(0)));

	// Set console size
	Console::SetWindow(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Console::drawRect( { 0,0 }, { 10,10 } );

	Console::Nocursortype();

	// Make the game loop
	Game game;
	while (game.IsRunning()) {
		game.ProcessInput();
		game.Update();
		game.LateUpdate();
		game.Draw();
	}

	return 0;
}