#pragma once
#include"Point.h"
#include<conio.h>

using namespace std;
#define MAXSIZESNAKE 100

class Snake;
class Food{
	friend class Snake;
private:
	Point food;	//food
public:
	Food();
};
class Snake{			//1 snake create form many points
private:
	Point* Cell[MAXSIZESNAKE];	//array of point to represent snake, snake's size max is 100
	int size;	//current size of snake
	bool isUpdateSize;	// true if snake eat food, otherwise false
	char dir;	//current director of snake
	Food fruit;	//food 
	int state;	//shows state of snake i.e living (1), dead (0), when create snake's state = 1
public:
	Snake();
	void addCell(int x, int y);	//add 1 point if snake eat food (size +1 )
	void TurnUp();				//Snake go up
	void TurnDown();			//Snake go down
	void TurnLeft();			//Snake go left
	void TurnRight();			//Snake go right
	void CheckDir();			//Check New direction from keyboard
	bool isDead();				//Check Dead
	void DrawSnake();			
	void Move();				//Snake's movement
	void ResetAll();						//reset dir
	void clearPoint(int x, int y);
	void clearAll();
};
