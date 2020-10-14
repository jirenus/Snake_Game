#include "Menu.h"
#include "Game.h"
#include <functional>

Menu::~Menu() {
	if (color) delete color;
}
void Menu::Draw()
{
	menuOuterBorder();
	menuInnerBorder();
	Title();
	for (int i = 0; i < heightBorder; i++)
	{
		Console::TextColor(color[i]);
		Console::gotoXY(SCREEN_WIDTH / 2 - lengthBorder / 2, SCREEN_HEIGHT / 2 - heightBorder / 2 + i);
		std::wcout << _items[i] << std::endl;
	}
}

Menu::Menu(const std::vector<std::wstring> items, std::function<void(unsigned int listitem)> onItemSelected) 
	: _selectedItem(0), OnItemSelected(onItemSelected) {
	
	_items = items;

	//set max length and height
	int maxLength = 0;
	for (int i = 0; i < items.size(); i++) {
		if (items[i].size() > maxLength)	maxLength = (unsigned int)items[i].size();
	}
	lengthBorder = maxLength;
	heightBorder = (int)items.size();

	//Console::clrscr();

	color = new int[ _items.size() ];

	// ?
	for (int i = 0; i < _items.size(); i++)	color[i] = MAUCHU;
	color[0] = MAUNEN;
}

void Menu::ProcessInput() {
	int key = _getch();

	Update(Status(key));
}

void Menu::OnActivate()
{
	PlaySound(L"sounds\\bkmusic.wav", NULL, SND_LOOP | SND_ASYNC);
	Draw();
}

void Menu::OnDeactivate()
{
	Console::ClearConsoleInputBuffer();
	system("cls");
}

void Menu::Update(Status key) {
	if ((int) key == 224) key = Status(_getch());

	if (key == Status::enter) {
		PlaySound(L"sounds\\menu-enter-x1.wav", NULL, SND_ASYNC);
	}

	switch (key)
	{
	case Status::up: {
		_selectedItem = (_selectedItem == 0) ? unsigned int (_items.size() - 1) : unsigned int(_selectedItem - 1);

		break;
	}

	case Status::down: {
		_selectedItem = (_selectedItem == _items.size() - 1) ? 0 : _selectedItem + 1;

		break;
	}

	case Status::enter: {
		Console::gotoXY(0, _selectedItem + 10);
		Console::TextColor(ColorCode_Black);

		//cls khong clear dc mau nen` 
		std::cout << "\t\t\t\t\t\t\t\t\t\t";

		OnItemSelected(_selectedItem);
		return;
	}
	}

	// Init color
	for (int i = 0; i < _items.size(); i++)
	{
		color[i] = MAUCHU;
	}
	color[_selectedItem] = MAUNEN;

	Draw();
}

void Menu::Title() {
	Console::gotoXY(0, 0);
	Console::TextColor(rand() % 10 + 1);

	std::vector<std::string> title = {
"   .-'''-. ,---.   .--.   ____    .--.   .--.      .-''-.   \n",
"  / _     \\|    \\  |  | .'  __ `. |  | _/  /     .'_ _   \\  \n",
" (`' )/`--'|  ,  \\ |  |/   '  \\  \\| (`' ) /     / ( ` )   ' \n",
"(_ o _).   |  |\\_ \\|  ||___|  /  ||(_ ()_)     . (_ o _)  | \n",
" (_,_). '. |  _( )_\\  |   _.-`   || (_,_)   __ |  (_,_)___| \n",
".---.  \\  :| (_ o _)  |.'   _    ||  |\\ \\  |  |'  \\   .---. \n",
"\\    `-'  ||  (_,_)\\  ||  _( )_  ||  | \\ `'   / \\  `-'    / \n",
" \\       / |  |    |  |\\ (_ o _) /|  |  \\    /   \\       /  \n",
"  `-...-'  '--'    '--' '.(_,_).' `--'   `'-'     `'-..-'   \n",
	};

	int marginLeft = (int)SCREEN_WIDTH / 2 - (int)title[0].size() / 2;
	int j = 0;
	for (auto i : title) {
		Console::gotoXY(marginLeft, j++);
		std::cout << i;
	}

}

void Menu::menuOuterBorder() {
	Console::gotoXY(0, 0);
	Console::TextColor(ColorCode_DarkYellow);

	std::vector<std::string> title = {
		"   _.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._.-=-._	\n",
		".-'---      - ---     --     ---   -----   - --       ----  ----   -     ---`-.\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(                                                                             )\n",
		" )                                                                           (	\n",
		"(___       _       _       _       _       _       _       _       _       ___)\n",
		"    `-._.-' (___ _) (__ _ ) (_   _) (__  _) ( __ _) (__  _) (__ _ ) `-._.-'	\n",
		"            `-._.-' (  ___) ( _  _) ( _ __) (_  __) (__ __) `-._.-'			\n",
		"                    `-._.-' (__  _) (__  _) (_ _ _) `-._.-'					\n",
		"                            `-._.-' (_ ___) `-._.-'							\n",
		"                                    `-._.-'									\n",
	};

	int j = 0;
	int marginLeft = (int) SCREEN_WIDTH / 2 - (int)title[0].size() / 2;
	for (auto i : title) {
		Console::gotoXY(marginLeft, j++);
		std::cout << i;
	}

	Console::TextColor(ColorCode_DarkWhite);
	Console::gotoXY(80, j++);
	std::cout << "Made by Bui Huynh Trung Nam";
	Console::gotoXY(88, j++);
	std::cout << "Ngo Truong Tuyen";
	Console::gotoXY(88, j++);
	std::cout << "Nguyen Trung Tin";
}
void Menu::menuInnerBorder() {
	//top and bottom border
	Console::TextColor(ColorCode_DarkGreen);
	for (int i = SCREEN_WIDTH / 2 - lengthBorder / 2 - 2; i <= SCREEN_WIDTH / 2 + lengthBorder / 2 + 2; i++) {
		Console::gotoXY(i, SCREEN_HEIGHT / 2 - heightBorder / 2 - 2);
		std::cout << (char)205;
		Console::gotoXY(i, SCREEN_HEIGHT / 2 + heightBorder / 2 + 2);
		std::cout << (char)205;
	}

	{	//4 corner
		Console::gotoXY(SCREEN_WIDTH / 2 - lengthBorder / 2 - 2, SCREEN_HEIGHT / 2 - heightBorder / 2 - 2);
		std::cout << (char)201;
		Console::gotoXY(SCREEN_WIDTH / 2 - lengthBorder / 2 - 2, SCREEN_HEIGHT / 2 + heightBorder / 2 + 2);
		std::cout << (char)200;

		Console::gotoXY(SCREEN_WIDTH / 2 + lengthBorder / 2 + 2, SCREEN_HEIGHT / 2 - heightBorder / 2 - 2);
		std::cout << (char)187;
		Console::gotoXY(SCREEN_WIDTH / 2 + lengthBorder / 2 + 2, SCREEN_HEIGHT / 2 + heightBorder / 2 + 2);
		std::cout << (char)188;
	}
	//left and right border
	for (int i = SCREEN_HEIGHT / 2 - heightBorder / 2 - 1; i <= SCREEN_HEIGHT / 2 + heightBorder / 2 + 1; i++) {
		Console::gotoXY(SCREEN_WIDTH / 2 - lengthBorder / 2 - 2, i);
		std::cout << (char)186;
		Console::gotoXY(SCREEN_WIDTH / 2 + lengthBorder / 2 + 2, i);
		std::cout << (char)186;
	}
}