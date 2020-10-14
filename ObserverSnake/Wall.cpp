#include "Wall.h"

Wall::Wall(int x, int y) : Object(x, y) { 
	_point = 0; 
}

void Wall::paint() {
	Console::TextColor(ColorCode_Grey);
	Console::gotoXY(_x, _y);

	std::cout << char(219);
}

int Wall::getPoint() { 
	return _point; 
}