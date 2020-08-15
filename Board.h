#pragma once
#include<iostream>
#include "Snake.h"

using namespace std;

class Board {
public:
	int PlayMode();
	void WelcomeScreen();
	void MainMenu(Snake& snake);
	void GameOverScreeen();
	void drawLines();
	void MapClassic();
};