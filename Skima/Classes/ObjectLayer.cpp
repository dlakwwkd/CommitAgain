#include "ObjectLayer.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "GameManager.h"
#include "Unit.h"
#include "Enums.h"


bool ObjectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_Hero = nullptr;

	return true;
}

//////////////////////////////////////////////////////////////////////////
void ObjectLayer::TickS(float dt)
{
	if (m_Hero == nullptr) return;
	
	m_Hero->Move(SINGLE);
	m_Hero->GetSprite()->setZOrder(-m_Hero->GetSprite()->getPosition().y);
	for (auto& b : m_MobList)
	{
		b->Move(SINGLE);
		b->GetSprite()->setZOrder(-b->GetSprite()->getPosition().y);
	}
}
void ObjectLayer::TickM(float dt)
{
	if (m_Hero == nullptr) return;

}
//////////////////////////////////////////////////////////////////////////



void ObjectLayer::CreateHero(int playerID, int unitID, Point location) // unitID를 넘어오는 playerID라 가정
{
	//todo unitType 맹글어야함

	std::shared_ptr<Unit> unit(new Unit("Images/SpookyPeas.png", location, 1.0f, MULTI));

	unit->SetUnitID(unitID);
	unit->SetUnitPlayerID(playerID);
	m_UnitList.push_back(unit);
	//m_Hero->GetBody()->setVelocityLimit(100);

	this->addChild(unit->GetSprite());
}

void ObjectLayer::UnitMove(Point pos, GameMode gameMode)
{
	if (m_Hero == nullptr) return;

	switch (gameMode)
	{
	case SINGLE:	UnitMoveS(pos);	break;
	case MULTI:		UnitMoveM(pos);	break;
	}
}


void ObjectLayer::FirstDrawUnit(int playerID, int unitID, UnitType unitType, Point pos)

{
	//todo unitType 넣어주기
	CreateHero(playerID, unitID, pos);
}
void ObjectLayer::UpdateAnimation(int playerId, int unitID, Point pos)
{
	for (auto& unit : m_UnitList)
	{
		if (unit->GetUnitID() == unitID){
			unit->GetSprite()->setAnchorPoint(Point(0.5, 0.5));
			unit->GetSprite()->setPosition(pos);
						
		}
	}
}



void ObjectLayer::AddNewSpriteAtPosition(Point pos)
{
	auto parent = dynamic_cast<PhysicsLayer*>(this->getParent());
	std::shared_ptr<Unit> unit(new Unit("Images/Pea.png", pos - parent->getPosition(), 1.0f, SINGLE));
	unit->GetBody()->setVelocityLimit(100);

	m_MobList.push_back(unit);
	this->addChild(unit->GetSprite());
}

void ObjectLayer::MobAi()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto parent = dynamic_cast<PhysicsLayer*>(this->getParent());

	for (auto& b : m_MobList)
	{
		if (b == m_Hero) continue;

		Vect temp;
		temp.x = rand() % (int)winSize.width;
		temp.y = rand() % (int)winSize.height;

		auto time = rand() % 300;

		if (time < 3)
			b->MoveTargeting(temp);
		else if (time == 10)
			b->MoveTargeting(m_Hero->GetBody()->getPosition());
		else
			continue;
	}
}


///////////////////////////////////////////////////////////////////////////
/*
	게임 모드에 따라 나뉘는 함수들
*/
///////////////////////////////////////////////////////////////////////////
void ObjectLayer::UnitMoveS(Point pos)
{
	m_Hero->MoveTargeting(pos);

	auto vect = m_Hero->GetBody()->getPosition();
	vect = GET_IM->GetMouseLocation() - vect;

	m_Hero->GetBody()->setVelocity(vect);
}
void ObjectLayer::UnitMoveM(Point pos)
{
	m_Hero->MoveTargeting(pos);
}




