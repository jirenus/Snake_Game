#pragma once
#include "Item.h"

class ThroughWall :
    public Item
{
public:
    void operate(std::shared_ptr<Snake> snake);
};

