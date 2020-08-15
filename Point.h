#pragma once
#include<iostream>

using namespace std;
#define MAXFRAME_X 50
#define MAXFRAME_Y 20
class Point{					//1 point has (x,y) on console
private:
	int x;
	int y;
public:
	Point();
	Point(int x, int y);
	void setPoint(int x, int y);		//set x, y for new point
	int getX();
	int getY();
	void moveUp();						// y--
	void moveDown();					//y++
	void moveLeft();					//x--
	void moveRight();					//x++
	void Draw(char ch = 'O');			//go to (x,y) of 1 point and draw it
	void Erase();						//go to (x,y) of 1 point and erase it
	void copyPos(Point* p);				//trace
	bool IsEqual(Point* p);				//compare 2 point 
	void Debug();						//show (x,y) on console to debug =))
};