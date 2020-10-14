#pragma once
#include "Console.h"
#include "Object.h"

class Wall : public Object {
private:
	int _point;
public:
	Wall(int x, int y);
	void paint();
	int getPoint();
};

