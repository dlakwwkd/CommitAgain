#include "pch.h"
#include "ObjectLayer.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "UILayer.h"
#include "Magician.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "Hero.h"
#include "Missile.h"
#include "Enums.h"
#include "TeleportEffect.h"
#include "LightningEffect.h"
#include "Unit.h"
#include "Skill.h"
#include "Laphinx.h"
#include "MoveRock.h"

#define GET_UI_LAYER	dynamic_cast<UILayer*>(this->getParent()->getParent()->getChildByName("UILayer"))

bool ObjectLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
void ObjectLayer::TickS(float dt)
{
}
void ObjectLayer::TickM(float dt)
{
}
//////////////////////////////////////////////////////////////////////////

void ObjectLayer::CreateHero(int playerID, int unitID, Vec2 location)
{
	std::shared_ptr<Hero> unit;
	switch (GET_SIDE_TYPE(unitID))
	{
	case HERO_MAGICIAN:	unit = std::make_shared<Magician>(location, 1.0f);	break;
	case HERO_JUPITER:	unit = std::make_shared<Jupiter>(location, 1.0f);	break;
	case HERO_LAPHINX:	unit = std::make_shared<Laphinx>(location, 1.0f);   break;
	default: return;
	}
	unit->SetUnitID(unitID);
	unit->SetUnitPlayerID(playerID);
	m_UnitList[unitID] = unit;
	m_HeroList[unitID] = unit;
	this->addChild(unit->GetSprite(), 16);

	if (playerID == TcpClient::getInstance()->getLoginId())
	{
		m_Hero = unit;
		unit->GetSprite()->addChild(unit->GetMyHpBar(), 16);
	}
	else
	{
		unit->GetSprite()->addChild(unit->GetOtherHpBar(), 16);
	}
	GET_UI_LAYER->UpdateHpBar(unit->GetCurHp(), unit->GetMaxHp());
}

void ObjectLayer::CreateMapObject(int unitID, Vec2 pos)
{
    //id로 타입 구별 먼저 해줘야 함
    m_UnitList[unitID] = std::make_shared<MoveRock>(unitID, pos);
}

void ObjectLayer::UnitMove(int unitID, Vec2 recvCurPos, Vec2 targetPos)
{
    switch (GET_GM.GetGameMode())
    {
	case SINGLE:	UnitMoveS(targetPos);								break;
	case MULTI:     UnitMoveM(unitID, recvCurPos, targetPos);			break;
    }
}

void ObjectLayer::UnitCrash(int unitID, Vec2 exPos)
{
    switch (GET_GM.GetGameMode())
    {
	case SINGLE:    UnitCrashS(exPos);									break;
	case MULTI:     UnitCrashM(unitID, exPos);							break;
    }
}

void ObjectLayer::UnitCrashEnd(int unitID, Vec2 revisePos)
{
    auto unit = m_HeroList.find(unitID);
    if (unit == m_HeroList.end())
    {
        return;
    }
    unit->second->SetTargetPos(revisePos);
    unit->second->EndCrash();
}

void ObjectLayer::UnitSkillUse(int unitID, SkillKey key, Vec2 recvCurPos, Vec2 targetPos)
{
    switch (GET_GM.GetGameMode())
    {
    case SINGLE:	UnitSkillUseS(key, targetPos);						break;
    case MULTI:     UnitSkillUseM(unitID, key, recvCurPos, targetPos);  break;
    }
}

void ObjectLayer::ShootMissile(int missileID, Vec2 createPos, Vec2 targetPos)
{
    switch (GET_GM.GetGameMode())
    {
    case SINGLE:    ShootMissileS(createPos, targetPos);				break;
    case MULTI:     ShootMissileM(missileID, createPos, targetPos);     break;
    }
}


void ObjectLayer::MissileCrash(int missileID)
{
    switch (GET_GM.GetGameMode())
    {
    case SINGLE:    MissileCrashS();									break;
    case MULTI:     MissileCrashM(missileID);							break;
    }
}

void ObjectLayer::UnitHpUpdate(int playerID, int unitID, int curHp)
{
    switch (GET_GM.GetGameMode())
    {
    case SINGLE:    UnitHpUpdateS(curHp);								break;
    case MULTI:     UnitHpUpdateM(playerID, unitID, curHp);				break;
    }
}

void ObjectLayer::DeleteMissile(int missileID)
{
    auto missile = m_MissileList.find(missileID);
    if (missile == m_MissileList.end())
    {
        return;
    }
    CC_SAFE_DELETE(missile->second);
    m_MissileList.erase(missile);
}


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


void ObjectLayer::UnitCrashS(Vec2 pos){}
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

void ObjectLayer::UnitSkillUseS(SkillKey key, Vec2 pos){}
void ObjectLayer::UnitSkillUseM(int unitID, SkillKey key, Vec2 recvCurPos, Vec2 targetPos)
{
    auto hero = m_HeroList.find(unitID);
    if (hero == m_HeroList.end())
    {
        return;
    }
    hero->second->SetTargetPos(targetPos);
    hero->second->GetSprite()->stopAllActions();
    hero->second->GetRealSprite()->stopAllActions();
    hero->second->SetSkillMotionByDir(key);
    hero->second->SkillCast(key, recvCurPos, targetPos);
}

void ObjectLayer::ShootMissileS(Vec2 createPos, Vec2 targetPos){}
void ObjectLayer::ShootMissileM(int missileID, Vec2 createPos, Vec2 targetPos)
{
    auto temp = m_MissileList.find(missileID);
    if (temp != m_MissileList.end())
    {
        temp->second->MissileDelete();
    }
    auto missile = new Missile(missileID);
	switch (GET_SIDE_TYPE(missileID))
    {
    case MS_FIRE_BALL:	missile->MissileCast("Images/fire.plist", 1200.0f, createPos, targetPos);   break;
    case MS_ICE_BALL:   missile->MissileCast("Images/ice.plist", 800.0f, createPos, targetPos);     break;
    case MS_SPARK:      missile->MissileCast("Jupiter/spark.plist", 1400.0f, createPos, targetPos); break;
    }
    m_MissileList[missileID] = missile;
}

void ObjectLayer::MissileCrashS(){}
void ObjectLayer::MissileCrashM(int missileID)
{
    auto missile = m_MissileList.find(missileID);
    if (missile == m_MissileList.end())
    {
        return;
    }
    missile->second->MissileCrash();
}

void ObjectLayer::UnitHpUpdateS(int curHp){}
void ObjectLayer::UnitHpUpdateM(int playerID, int unitID, float curHP)
{
    auto unit = m_UnitList.find(unitID);
    if (unit == m_UnitList.end())
    {
        return;
    }
    if (GET_MAIN_TYPE(unitID) == UNIT_OBSTRUCT)
    {
        return;
    }
    unit->second->SetHp(curHP);

    if (m_Hero->GetUnitPlayerID() == playerID)
    {
		GET_UI_LAYER->UpdateHpBar(unit->second->GetCurHp(), unit->second->GetMaxHp());
		unit->second->UpdateMyHpBar();
	}
	else
	{
		unit->second->UpdateOtherHpBar();
	}
}
