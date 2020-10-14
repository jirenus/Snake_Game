#pragma once
#include "Console.h"
#include "Object.h"
#include <iostream>

class Fruit : public Object {
private:
	int _point;
public:
	Fruit(int x, int y);
	~Fruit();

	void paint();
	int getPoint();
};

