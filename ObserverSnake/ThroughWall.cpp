#include "ThroughWall.h"
#include "Snake.h"

void ThroughWall::operate(std::shared_ptr<Snake> snake)
{
	snake->setThroughWall(30);
}
