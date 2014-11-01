#pragma once
#include "Unit.h"
class Player
{
public:
	Player();
	~Player();

public:
	void UnitMove(N_Point currentPos, N_Point targetPos, int speed);

private:
	Unit* mUnit;
};

