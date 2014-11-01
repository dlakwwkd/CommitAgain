#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	mUnit = new Unit();
}


Player::~Player()
{
	delete mUnit;
}

void Player::UnitMove(Point currentPos, Point targetPos, int speed)
{

}

