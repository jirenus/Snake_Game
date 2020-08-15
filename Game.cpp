#include "Game.h"

Game::Game()
{
	board = nullptr;
	snake = nullptr;
	running = false;
}

Game::~Game()
{
}

void Game::init()
{
	Nocursortype(); //hide pointer
	srand((unsigned)time(NULL));

	snake = new Snake(); //object to play

	running = true;

	board->WelcomeScreen();
	// int option = board->PlayMode();
}

void Game::handleEvents()
{
	int playAgain = 0;

	do
	{
		system("cls");
		board->drawLines();
		// board->MapClassic();

		char op;
		do
		{
			if (_kbhit())
			{
				op = _getch();
				switch (op)
				{
				case 'w':
				case 'W':
					snake->TurnUp();
					break;
				case 's':
				case 'S':
					snake->TurnDown();
					break;
				case 'a':
				case 'A':
					snake->TurnLeft();
					break;
				case 'd':
				case 'D':
					snake->TurnRight();
					break;
				}
			}
			snake->Move();
		} while (!snake->isDead()); //q = quit

		board->GameOverScreeen();
		std::cin >> playAgain;
	} while (playAgain == 1);
}

void Game::update()
{
}

void Game::render()
{
}

void Game::clean()
{
}

bool Game::isRunning()
{
	return running;
}
