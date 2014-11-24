#include "pch.h"
#include "ObjectLayer.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "Magician.h"
#include "GameManager.h"
#include "Hero.h"
#include "Missile.h"
#include "FireballMissile.h"
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
	
	m_Hero->Move();
	m_Hero->GetSprite()->setZOrder(-m_Hero->GetSprite()->getPosition().y);
	for (auto& b : m_MobList)
	{
		b->Move();
		b->GetSprite()->setZOrder(-b->GetSprite()->getPosition().y);
	}
}
void ObjectLayer::TickM(float dt)
{
// 	for (auto& unit : m_UnitList)
// 	{
// 		unit.second->Movement();
// 	}
}
//////////////////////////////////////////////////////////////////////////



void ObjectLayer::FirstDrawUnit(int playerID, int unitID, HeroType heroType, Point pos)
{
	//todo unitType 넣어주기
	CreateHero(playerID, unitID, pos, heroType);
}

void ObjectLayer::CreateHero(int playerID, int unitID, Point location, HeroType heroType)
{
	std::shared_ptr<Hero> unit;

	switch (heroType)
	{
	case HERO_NONE:
		return;
	case HERO_MAGICIAN:
		std::shared_ptr<Hero> temp(new Magician(location, 1.0f));
		unit = temp;
		break;
	}

	unit->SetUnitID(unitID);
	unit->SetUnitPlayerID(playerID);
	m_UnitList[unitID] = unit;

	if (playerID == TcpClient::getInstance()->getLoginId())
	{
		m_Hero = unit;
	}
	this->addChild(unit->GetSprite());
}

void ObjectLayer::UnitMove(int unitID, Point recvCurPos, Point targetPos)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		UnitMoveS(targetPos);
		break;
	case MULTI:
		UnitMoveM(unitID, recvCurPos, targetPos);
		break;
	}
}

void ObjectLayer::UnitCrash(int unitID, Point recvPos)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		UnitCrashS(recvPos);
		break;
	case MULTI:
		UnitCrashM(unitID, recvPos);
		break;
	}
}

void ObjectLayer::UnitCrashEnd(int unitID, Point revisePos)
{
	m_Hero->SetMoveTargetPos(revisePos);
	m_UnitList[unitID]->EndCrash();
}

void ObjectLayer::UnitSkillUse(int unitId, SkillKey key, Point recvCurPos, Point targetPos)
{


	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		UnitSkillUseS(key, targetPos);
		break;
	case MULTI:
		UnitSkillUseM(unitId, key, recvCurPos, targetPos);
		break;
	}
}


void ObjectLayer::ShootMissile(int missileID, Point createPos, Point targetPos)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		ShootMissileS(createPos, targetPos);
		break;
	case MULTI:
		ShootMissileM(missileID, createPos, targetPos);
		break;
	}
}


void ObjectLayer::MissileCrash(int missileID)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		MissileCrashS();
		break;
	case MULTI:
		MissileCrashM(missileID);
		break;
	}
}


void ObjectLayer::DeleteMissile(int missileID)
{
	for (auto& iter = m_MissileList.begin(); iter != m_MissileList.end(); ++iter)
	{
		if (iter->first == missileID)
		{
			m_MissileList.erase(iter);
			break;
		}
	}
}

// 
// void ObjectLayer::AddNewSpriteAtPosition(Point pos)
// {
// 	auto parent = dynamic_cast<PhysicsLayer*>(this->getParent());
// 	std::shared_ptr<Unit> unit(new Unit("Images/Pea.png", pos - parent->getPosition(), 1.0f));
// 	unit->GetBody()->setVelocityLimit(100);
// 
// 	m_MobList.push_back(unit);
// 	this->addChild(unit->GetSprite());
// }
// 
// void ObjectLayer::MobAi()
// {
// 	auto winSize = Director::getInstance()->getWinSize();
// 	auto parent = dynamic_cast<PhysicsLayer*>(this->getParent());
// 
// 	for (auto& b : m_MobList)
// 	{
// 		if (b == m_Hero) continue;
// 
// 		Vect temp;
// 		temp.x = rand() % (int)winSize.width;
// 		temp.y = rand() % (int)winSize.height;
// 
// 		auto time = rand() % 300;
// 
// 		if (time < 3)
// 			b->SetMoveTargetPos(temp);
// 		else if (time == 10)
// 			b->SetMoveTargetPos(m_Hero->GetBody()->getPosition());
// 		else
// 			continue;
// 	}
// }



///////////////////////////////////////////////////////////////////////////
/*
	게임 모드에 따라 나뉘는 함수들
*/
///////////////////////////////////////////////////////////////////////////
void ObjectLayer::UnitMoveS(Point pos)
{
// 	m_Hero->SetMoveTargetPos(pos);
// 	m_Hero->TryMove();

// 	auto vect = m_Hero->GetBody()->getPosition();
// 	vect = GET_IM->GetMouseLocation() - vect;
// 
// 	m_Hero->GetBody()->setVelocity(vect);
}
void ObjectLayer::UnitMoveM(int unitID, Point recvCurPos, Point targetPos)
{
	m_UnitList[unitID]->SetMoveTargetPos(targetPos);
	m_UnitList[unitID]->TryMove();
}


void ObjectLayer::UnitCrashS(Point pos)
{

}

void ObjectLayer::UnitCrashM(int unitID, Point recvPos)
{
	m_UnitList[unitID]->SetMoveTargetPos(recvPos);
	m_UnitList[unitID]->Crashed();
}

void ObjectLayer::UnitSkillUseS(SkillKey key, Point pos)
{

}

void ObjectLayer::UnitSkillUseM(int unitID, SkillKey key, Point recvCurPos, Point targetPos)
{
	m_UnitList[unitID]->EndMove();
}

void ObjectLayer::ShootMissileS(Point createPos, Point targetPos)
{

}

void ObjectLayer::ShootMissileM(int missileID, Point createPos, Point targetPos)
{
	std::shared_ptr<Missile> missile;

	switch (m_Hero->GetHeroType())
	{
	case HERO_MAGICIAN:
		{
			std::shared_ptr<Missile> temp(new FireballMissile());
			missile = temp;
		}
		break;
	case HERO_NONE:
		return;
	}
	missile->SetUnitID(missileID);
	missile->MissileCast(createPos, targetPos);

	m_MissileList[missileID] = missile;
}

void ObjectLayer::MissileCrashS()
{

}

void ObjectLayer::MissileCrashM(int missileID)
{
	m_MissileList[missileID]->MissileCrash();
}


