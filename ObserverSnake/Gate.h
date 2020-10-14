#pragma once
#include "Console.h"
#include "Object.h"
#include <iostream>

// Gate is load first from file, it is invisible on board, 
//to get to gate, player need to have enough score
enum class GateCollisionType {
	none,
	border,
	door
};

class Gate : public Object {
private:
	int _point;
public:
	Gate(int x, int y);
	void paint();
	int getPoint();
};

