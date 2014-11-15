#include "stdafx.h"
#include "ClientSession.h"
#include "ClientManager.h"
#include "GameManager.h"
#include "Unit.h"


Unit::Unit(int playerId, b2Vec2 pos)
{
	static int makeId = 0;
	m_UnitID = ++makeId;
	m_Hp = 0;

}

Unit::Unit()
{

}

Unit::~Unit()
{
	GGameManager->GetWolrd()->DestroyBody(m_Body);
}

