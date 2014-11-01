#pragma once
#include "Unit.h"
class Player
{
public:
	Player();
	~Player();

public:
	void UnitMove(Point currentPos, Point targetPos, int speed);

private:
	Unit* mUnit;
};

