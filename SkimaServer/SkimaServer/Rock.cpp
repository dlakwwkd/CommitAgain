#include "stdafx.h"
#include "Rock.h"
#include "GameManager.h"


Rock::Rock(Player* owner, const b2Vec2& pos)
{
	SetStaticBody(owner, OS_ROCK, pos, b2Vec2(30.0f, 60.0f));
	m_Hp = 1000;
}


Rock::~Rock()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
}
