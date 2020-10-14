#pragma once
#include "Console.h"
#include "Object.h"
#include <iostream>

class SnakeSegment : public Object {
friend class Snake;
private:
	int _color;
	char _character;
public:
	SnakeSegment(int x, int y);
	void setColor(int color) { _color = color; }
	void setCharacter(char character) { _character = character; }

	void paint();
};

