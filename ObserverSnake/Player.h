#pragma once
#include <iostream>
#include"Console.h"


struct Skin {
	wchar_t character;
	int color;
	int price;
};

class Player {
private:
	unsigned int currentScore;	//arr use to save current score of 4 maps
	unsigned int totalScore;		//arr use to save total score of each map

	// required
	int _skillUIMarginLeft;

	//
	Skin _snakeSkin;
	
public:
	Player(int skillUIMarginLeft);
	void resetScore();
	void addScore(int score = 10);
	unsigned int getCurrentScore();
	unsigned int getTotalScore();
	void setTotalScore(unsigned int score) { totalScore = score; }

	void saveScore();
	void showCurrentScore();

	Skin& getSnakeSkin();

	int getSkillUIMarginLeft() { return _skillUIMarginLeft; };

	void setSnakeSkin(Skin skin) { _snakeSkin = skin; }
};

