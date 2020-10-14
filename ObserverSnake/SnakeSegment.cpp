#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(int x, int y) : Object(x, y), _character('O'), _color(ColorCode_Green) {

}

void SnakeSegment::paint() {
	Console::TextColor(_color);
	Console::gotoXY(_x, _y);
	std::cout << _character;
}