#include"Point.h"
#include"Console.h"
Point::Point() {
	x = y = 10;
}
Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}
void Point::setPoint(int x, int y) {
	this->x = x;
	this->y = y;
}
int Point::getX() {
	return this->x;
}
int Point::getY() {
	return this->y;
}
void Point::moveUp() {
	y--;
	if (y < 1)	y = MAXFRAME_Y;

}
void Point::moveDown() {
	y++;
	if (y > MAXFRAME_Y) y = 1;
}
void Point::moveLeft() {
	x--;
	if (x < 1)	x = MAXFRAME_X;
}
void Point::moveRight() {
	x++;
	if (x > MAXFRAME_X) x = 1;
}
void Point::Draw(char ch) {
	gotoXY(x, y);
	cout << ch;
}
void Point::Erase() {
	gotoXY(x, y);
	cout << " ";
}
void Point::copyPos(Point* p){
	p->x = x;
	p->y = y;
}
bool Point::IsEqual(Point* p){
	if (p->x == x && p->y == y)	return true;
	return false;
}
void Point::Debug() {
	cout << " (" << x << "," << y << ") ";
}