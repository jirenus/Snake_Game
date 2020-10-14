#pragma once
#include <iostream>
#include "Console.h"

class Object {
protected:
	int _x;
	int _y;

	// Default value for width and height are 1
	int _width;
	int _height;
public:
	Object(int x, int y);
	virtual ~Object();

	void clearBlock();

	int getWidth();
	int getHeight();

	int getX();
	int getY();

	void setPos(int x, int y);

	virtual void paint() = 0;

	// use by snake to boost progress
	virtual void operate() {};
};

