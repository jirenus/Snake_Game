#include"Player.h"

Player::Player(int skillUIMarginLeft) : _skillUIMarginLeft(skillUIMarginLeft) {
	currentScore = 0;
	totalScore = 0;
	_snakeSkin = { 'O', ColorCode_DarkGreen, 0 };
}
void Player::resetScore() {
	currentScore = 0;
}
void Player::addScore(int score) {
	currentScore += score;
	totalScore += score;
}
unsigned int Player::getCurrentScore() {
	return currentScore;
}
unsigned int Player::getTotalScore() {
	return totalScore;
}

void Player::saveScore() {
	totalScore += currentScore;
}

void Player::showCurrentScore() {
	Console::gotoXY(_skillUIMarginLeft - 4, 3);
	std::cout << "Total Score: " << totalScore;
	Console::gotoXY(_skillUIMarginLeft - 4, 4);
	std::cout << "Your Score: " << currentScore;
}

Skin& Player::getSnakeSkin() {
	return _snakeSkin;
}