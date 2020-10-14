#include "Rocket.h"
#include "Snake.h"

void Rocket::operate(std::shared_ptr<Snake> snake)
{
	snake->setSpeed(2.0);
}
