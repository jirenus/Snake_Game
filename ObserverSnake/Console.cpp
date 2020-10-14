#include <stdio.h>
#include <conio.h>
#include "console.h"
#include <iostream>

//-------------------------Screen-------------------------
void Console::clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void Console::SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}

//screen: goto (x,y)
void Console::gotoXY(int column, int line) {
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Console::TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Console::Nocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void Console::drawRect(Coord start, Coord end, int color) {
	TextColor(color);

	//top
	gotoXY(start.X, start.Y);
	for (int i = start.X; i < end.X + 1; i++) {
		std::cout << char(196);
	}
	//bottom
	gotoXY(start.X, end.Y);
	for (int i = start.X; i < end.X + 1; i++) {
		std::cout << char(196);
	}
	//left
	for (int i = start.Y; i < end.Y + 1; i++) {
		gotoXY(start.X, i);
		std::cout << char(179);
	}
	//right
	for (int i = start.Y; i < end.Y + 1; i++) {
		gotoXY(end.X, i);
		std::cout << char(179);
	}

	// angle
	gotoXY(start.X, start.Y);
	std::cout << char(218);

	gotoXY(end.X, start.Y);
	std::cout << char(191);

	gotoXY(start.X, end.Y);
	std::cout << char(192);

	gotoXY(end.X, end.Y);
	std::cout << char(217);

}

void Console::ClearConsoleInputBuffer()
{
	PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
	DWORD ClearingVar2;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), ClearingVar1, 256, &ClearingVar2);
	delete[] ClearingVar1;
}
