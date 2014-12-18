#include "stdafx.h"
#include "MoveRock.h"
#include "GameManager.h"


MoveRock::MoveRock(Player* owner, const b2Vec2& pos)
{
	SetDynamicBody(owner, OS_MOVE_ROCK, pos, 30.0f);
    m_Hp = 1000;
}


MoveRock::~MoveRock()
{
}
