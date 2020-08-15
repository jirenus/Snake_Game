#include"Board.h"
#include"Console.h"
#include"Control.h"
#include"Point.h"

#define TOUCH_LINE_TOP 0
#define TOUCH_LINE_BOTTOM (MAXFRAME_Y + 1)
#define TOUCH_LINE_LEFT 0
#define TOUCH_LINE_RIGHT (MAXFRAME_X + 1)

int Board::PlayMode(){
	int option;
	//TODO: store menu in a string array
	TextColor(ColorCode_Blue);
	cout<<	"1.New Game (1 player)" << endl;
	TextColor(ColorCode_Red);
	cout << "2.New Game (2 players)  //chua lam" << endl;
	TextColor(ColorCode_White);
	cout << "3.High Score  //chua lam" << endl;
	TextColor(ColorCode_Pink);
	cout << "4.Exit  //chua lam" << endl;
	TextColor(ColorCode_Cyan);
	cout << "Enter your choose: ";
	cin >> option;
	return option;
}
void Board::WelcomeScreen(){
	cout << "_________________     __                      __           _        _____________" << endl;
	cout << "|                     | |          |         /  |          |    /   |" << endl;
	cout << "|                     |  |         |        /    |         |   /    |" << endl;
	cout << "|                     |   |        |       /      |        |  /     |" << endl;
	cout << "|________________     |    |       |      /        |       | /      |" << endl;
	cout << "                 |    |     |      |     / ======== |      |/       |============" << endl;
	cout << "                 |    |      |     |    /            |     ||       |" << endl;
	cout << "                 |    |       |    |   /              |    | |      |" << endl;
	cout << "                 |    |        |   |  /                |   |  |     |" << endl;
	cout << "=================     |         |__| /                  |  |   |    |_____________" << endl;
	cout << endl;
}
void Board::GameOverScreeen() {
	TextColor(ColorCode_Cyan);
	gotoXY(15, 8);
	cout << "GAME OVER !!!";
	gotoXY(15, 9);
	cout << "Do you want to play again ?";
	gotoXY(15, 10);
	cout << "1. Yes";
	gotoXY(15, 11);
	cout << "2. No";
	gotoXY(15, 12);
	cout << "Your Chose: ";
}

void Board::drawLines() {
	int xIndex, yIndex;
	//it will be changed when we have more information 
	//draw line at the top of program
	xIndex = 0, yIndex = TOUCH_LINE_TOP;
	while (xIndex <= TOUCH_LINE_RIGHT) {
		gotoXY(xIndex, yIndex);
		cout << "+";
		xIndex++;
	}

	//draw line at the bottom of program
	xIndex = 0, yIndex = TOUCH_LINE_BOTTOM;
	while (xIndex <= TOUCH_LINE_RIGHT) {
		gotoXY(xIndex, yIndex);
		cout << "+";
		xIndex++;
	}

	//draw line at the left of program
	xIndex = TOUCH_LINE_LEFT, yIndex = 0;
	while (yIndex <= TOUCH_LINE_BOTTOM) {
		gotoXY(xIndex, yIndex);
		cout << "+";
		yIndex++;
	}

	//draw line at the right of program
	xIndex = TOUCH_LINE_RIGHT, yIndex = 0;
	while (yIndex <= TOUCH_LINE_BOTTOM) {
		gotoXY(xIndex, yIndex);
		cout << "+";
		yIndex++;
	}

}
void Board::MapClassic() {
	TextColor(ColorCode_Cyan);
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "A                                                 A" << endl;
	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
}