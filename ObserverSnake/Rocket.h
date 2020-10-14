#pragma once
#include "Item.h"
class Rocket :
    public Item
{
public:
    void operate(std::shared_ptr<Snake> snake);
};

