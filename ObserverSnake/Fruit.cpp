#include "Fruit.h"

Fruit::Fruit(int x, int y) : Object(x, y) {
	_point = 0; 
}

Fruit::~Fruit()
{

}

void Fruit::paint() {
	Console::TextColor(ColorCode_Red);
	Console::gotoXY(_x, _y);
	std::cout << '#';
}

int Fruit::getPoint() { 
	return _point; 
}