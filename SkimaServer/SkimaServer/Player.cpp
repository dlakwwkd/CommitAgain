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

void Player::UnitMove(N_Point currentPos, N_Point targetPos, int speed)
{

}

