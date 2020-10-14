#include "Gift.h"

Gift::Gift(int x, int y) : Object(x, y) {
}

void Gift::paint() {
	Console::TextColor(ColorCode_Cyan);

	Console::gotoXY(_x, _y);
	std::cout << "?";
}
