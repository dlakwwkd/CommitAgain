﻿#include "pch.h"
#include "ObjectLayer.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "UILayer.h"
#include "Magician.h"
#include "GameManager.h"
#include "Hero.h"
#include "Missile.h"
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
// 	if (m_Hero == nullptr) return;
// 	
// 	m_Hero->Move();
// 	m_Hero->GetSprite()->setZOrder(-m_Hero->GetSprite()->getPosition().y);
// 	for (auto& b : m_MobList)
// 	{
// 		b->Move();
// 		b->GetSprite()->setZOrder(-b->GetSprite()->getPosition().y);
// 	}
}
void ObjectLayer::TickM(float dt)
{
// 	for (auto& unit : m_UnitList)
// 	{
// 		unit.second->Movement();
// 	}
}
//////////////////////////////////////////////////////////////////////////



void ObjectLayer::FirstDrawUnit(int playerID, int unitID, Vec2 pos)
{
	//todo unitType 넣어주기
	CreateHero(playerID, unitID, pos);
}

void ObjectLayer::CreateHero(int playerID, int unitID, Vec2 location)
{
	std::shared_ptr<Hero> unit;

	auto heroType = unitID & 0x0F000000;
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
	this->addChild(unit->GetSprite(),16);
	unit->GetSprite()->addChild(unit->GetHpBar(),16);
}

void ObjectLayer::UnitMove(int unitID, Vec2 recvCurPos, Vec2 targetPos)
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

void ObjectLayer::UnitCrash(int unitID, Vec2 exPos)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		UnitCrashS(exPos);
		break;
	case MULTI:
		UnitCrashM(unitID, exPos);
		break;
	}
}

void ObjectLayer::UnitCrashEnd(int unitID, Vec2 revisePos)
{
	auto unit = m_UnitList.find(unitID);
	if (unit == m_UnitList.end())
	{
		return;
	}
	unit->second->SetTargetPos(revisePos);
	unit->second->EndCrash();
}

void ObjectLayer::UnitSkillUse(int unitId, SkillKey key, Vec2 recvCurPos, Vec2 targetPos)
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


void ObjectLayer::ShootMissile(int missileID, Vec2 createPos, Vec2 targetPos)
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

void ObjectLayer::UnitHpUpdate(int playerID, int unitID, int curHp)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		UnitHpUpdateS(curHp);
		break;
	case MULTI:
		UnitHpUpdateM(playerID, unitID, curHp);
		break;
	}
}

void ObjectLayer::DeleteMissile(int missileID)
{
	auto missile = m_MissileList.find(missileID);
	if (missile == m_MissileList.end())
	{
		return;
	}
	GET_MM->Release(missile->second);
	m_MissileList.erase(missile);
}
void ObjectLayer::UnitTeleport(int unitID, Vec2 recvCurPos, Vec2 targetPos)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		UnitTeleportS(targetPos);
		break;
	case MULTI:
		UnitTeleportM(unitID, recvCurPos, targetPos);
		break;
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
void ObjectLayer::UnitMoveS(Vec2 pos)
{
// 	m_Hero->SetMoveTargetPos(pos);
// 	m_Hero->TryMove();

// 	auto vect = m_Hero->GetBody()->getPosition();
// 	vect = GET_IM->GetMouseLocation() - vect;
// 
// 	m_Hero->GetBody()->setVelocity(vect);
}
void ObjectLayer::UnitMoveM(int unitID, Vec2 recvCurPos, Vec2 targetPos)
{
	auto unit = m_UnitList.find(unitID);
	if (unit == m_UnitList.end())
	{
		return;
	}
	unit->second->SetTargetPos(targetPos);
	unit->second->TryMove();
}


void ObjectLayer::UnitCrashS(Vec2 pos)
{

}

void ObjectLayer::UnitCrashM(int unitID, Vec2 exPos)
{
	auto unit = m_UnitList.find(unitID);
	if (unit == m_UnitList.end())
	{
		return;
	}
	unit->second->SetTargetPos(exPos);
	unit->second->Crashed();
}

void ObjectLayer::UnitSkillUseS(SkillKey key, Vec2 pos)
{

}

void ObjectLayer::UnitSkillUseM(int unitID, SkillKey key, Vec2 recvCurPos, Vec2 targetPos)
{
	auto unit = m_UnitList.find(unitID);
	if (unit == m_UnitList.end())
	{
		return;
	}
	unit->second->SetTargetPos(targetPos);
	unit->second->SetMoveMotionByDir();
	unit->second->EndMove();
}

void ObjectLayer::ShootMissileS(Vec2 createPos, Vec2 targetPos)
{

}

void ObjectLayer::ShootMissileM(int missileID, Vec2 createPos, Vec2 targetPos)
{
	auto temp = m_MissileList.find(missileID);
	if (temp != m_MissileList.end())
	{
		temp->second->MissileDelete();
	}

    auto missile = static_cast<Missile*>(GET_MM->Assign(missileID));
    auto missileType = UnitType(missileID & 0x0F000000);
    missile->SetType(missileType);
    switch (missileType)
    {
    case MS_FIRE_BALL:
        missile->MissileCast("Images/fire.plist", 1200.0f, createPos, targetPos);
        break;
    case MS_ICE_BALL:
        missile->MissileCast("Images/ice.plist", 800.0f, createPos, targetPos);
        break;
    }
	m_MissileList[missileID] = missile;
}

void ObjectLayer::MissileCrashS()
{

}

void ObjectLayer::MissileCrashM(int missileID)
{
	auto missile = m_MissileList.find(missileID);
	if (missile == m_MissileList.end())
	{
		return;
	}
	missile->second->MissileCrash();
}

void ObjectLayer::UnitHpUpdateS(int curHp)
{

}

void ObjectLayer::UnitHpUpdateM(int playerID, int unitID, float curHP)
{
	auto unit = m_UnitList.find(unitID);
	if (unit == m_UnitList.end())
	{
		return;
	}
	unit->second->SetHp(curHP);
	unit->second->UpdateHpBar();

	if (m_Hero->GetUnitPlayerID() == playerID)
	{
		auto layer = dynamic_cast<UILayer*>(this->getParent()->getParent()->getChildByName("UILayer"));
		layer->UpdateHpBar(unit->second->GetCurHp(), unit->second->GetMaxHp());
	}
}

void ObjectLayer::UnitTeleportS(Vec2 targetPos)
{

}

void ObjectLayer::UnitTeleportM(int unitID, Vec2 curPos, Vec2 targetPos)
{
	auto unit = m_UnitList.find(unitID);
	if (unit == m_UnitList.end())
	{
		return;
	}
	unit->second->SetTargetPos(targetPos);
	unit->second->SetMoveMotionByDir();
	unit->second->TryTeleport();
}

