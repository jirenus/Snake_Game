#pragma once
#include "Item.h"

class X2Point :
    public Item
{
public:
    void operate(std::shared_ptr<Snake> snake);
};

