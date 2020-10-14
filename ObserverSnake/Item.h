#pragma once
#include <string>
#include <memory>

class Snake;

// Item on slot that snake can use to boost
class Item
{
public:
	virtual void operate(std::shared_ptr<Snake> snake) = 0;
};
