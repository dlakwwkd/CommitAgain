﻿#include "pch.h"
#include "ObjectLayer.h"
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
#include "RockEffect.h"
#include "Unit.h"
#include "Skill.h"
#include "Laphinx.h"
#include "Rock.h"
#include "MoveRock.h"
#include "Lava.h"
#include "Mob.h"
#include "MeteorSkill.h"
//#define GET_UI_LAYER	dynamic_cast<UILayer*>(this->getParent()->getParent()->getChildByName("UILayer"))

bool ObjectLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
void ObjectLayer::Tick(float dt)
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
        unit->SetMyHpBar();
    }
    else
    {
        unit->SetEnemyHpBar();
    }
    GET_UI_LAYER->UpdateHpBar(unit->GetCurHp(), unit->GetMaxHp());
}

void ObjectLayer::CreateMapObject(int unitID, Vec2 pos)
{
    switch (GET_SIDE_TYPE(unitID))
    {
    case OS_ROCK:
        m_UnitList[unitID] = std::make_shared<Rock>(unitID, pos);
        break;
    case OS_MOVE_ROCK:
        m_UnitList[unitID] = std::make_shared<MoveRock>(unitID, pos);
        break;
    case OS_LAVA:
        m_UnitList[unitID] = std::make_shared<Lava>(unitID, pos);
        break;

    default:
        break;
    }
}

void ObjectLayer::CreateMob(int playerID, int unitID, Vec2 location)
{
    std::shared_ptr<Mob> unit;
    switch (GET_SIDE_TYPE(unitID))
    {
    case MOB_PEA:	unit = std::make_shared<Mob>(location, 1.0f);	break;
    default: return;
    }
    unit->SetUnitID(unitID);
    unit->SetUnitPlayerID(playerID);
    m_UnitList[unitID] = unit;
    this->addChild(unit->GetSprite(), 16);

    if (playerID == TcpClient::getInstance()->getLoginId())
    {
        unit->SetMyHpBar();
    }
    else
    {
        unit->SetEnemyHpBar();
    }
}

void ObjectLayer::UnitMove(int unitID, Vec2 recvCurPos, Vec2 targetPos)
{
    auto unit = m_UnitList.find(unitID);
    if (unit == m_UnitList.end())
    {
        return;
    }
    unit->second->SetTargetPos(targetPos);
    unit->second->TryMove();
}

void ObjectLayer::UnitCrash(int unitID, Vec2 exPos)
{
    auto unit = m_UnitList.find(unitID);
    if (unit == m_UnitList.end())
    {
        return;
    }
    unit->second->SetTargetPos(exPos);
    unit->second->Crashed();
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

void ObjectLayer::UnitSkillUse(int playerID,int unitID, SkillKey key, Vec2 recvCurPos, Vec2 targetPos)
{
    auto hero = m_HeroList.find(unitID);
    if (hero == m_HeroList.end())
    {
        return;
    }
    
    if (hero->second->GetHeroType() == HERO_LAPHINX && key == SKILL_Q)
    {
        hero->second->SetTargetPos(targetPos);
        hero->second->GetSprite()->stopAllActions();
        hero->second->GetRealSprite()->stopAllActions();
        hero->second->SetSkillMotionByDir(key);

        if (m_Hero->GetUnitPlayerID()==playerID)
        {
            hero->second->SkillCast(key, recvCurPos, targetPos);
        }
        else
        {
            hero->second->SkillCastForEnemy(key, recvCurPos, targetPos);
        }
    }
    else
    {
        hero->second->SetTargetPos(targetPos);
        hero->second->GetSprite()->stopAllActions();
        hero->second->GetRealSprite()->stopAllActions();
        hero->second->SetSkillMotionByDir(key);
        hero->second->SkillCast(key, recvCurPos, targetPos);
    }
    
}
void ObjectLayer::UnitHpUpdate(int playerID, int unitID, int curHp)
{
    auto unit = m_UnitList.find(unitID);
    if (unit == m_UnitList.end())
    {
        return;
    }
    unit->second->SetHp(curHp);

    if (curHp <= 0)
    {
        switch (GET_MAIN_TYPE(unitID))
        {
        case UNIT_OBSTRUCT:
        {
            auto mapObject = std::dynamic_pointer_cast<MapObject>(unit->second);
            mapObject->MapObjectBreak();
            m_UnitList.erase(unit);
        }
            break;
        case UNIT_MOB:
        {
            this->removeChild(unit->second->GetSprite());
            m_UnitList.erase(unit);
        }
            break;
        }
        return;
    }
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

void ObjectLayer::UnitBuffApply(int unitID, float bonus, BuffTarget type)
{
    auto unit = m_UnitList.find(unitID);
    if (unit == m_UnitList.end())
    {
        return;
    }
    switch (type)
    {
    case BUFF_HP:       unit->second->SetHp(unit->second->GetCurHp() + bonus);      break;
    case BUFF_SPEED:    unit->second->SetSpeed(unit->second->GetSpeed() + bonus);   break;
    default:
        break;
    }
}


void ObjectLayer::ShootMissile(int missileID, Vec2 createPos, Vec2 targetPos)
{
    auto temp = m_MissileList.find(missileID);
    if (temp != m_MissileList.end())
    {
        temp->second->MissileDelete();
    }
    auto missile = new Missile(missileID);
    switch (GET_SIDE_TYPE(missileID))
    {
    case MS_FIRE_BALL:	missile->MissileCast("Images/fire.plist", "Music/Effect/fireballshoot.mp3", 1000.0f, createPos, targetPos);   break;
    case MS_ICE_BALL:   missile->MissileCast("Images/ice.plist", "", 800.0f, createPos, targetPos);     break;
    case MS_SPARK:      missile->MissileCast("Jupiter/spark.plist","", 1300.0f, createPos, targetPos); break;
    }
    m_MissileList[missileID] = missile;
}

void ObjectLayer::MissileCrash(int missileID)
{
    auto missile = m_MissileList.find(missileID);
    if (missile == m_MissileList.end())
    {
        return;
    }
    missile->second->MissileCrash();
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

void ObjectLayer::UnHide(int playerID, int unitID, Vec2 recvCurPos)
{
    auto hero = m_HeroList.find(unitID);
    if (hero == m_HeroList.end())
    {
        return;
    }

    if (hero->second->GetHeroType() == HERO_LAPHINX)
    {
        hero->second->HeroUnHide(recvCurPos);

    }
}

void ObjectLayer::MeteorCreate(int playerID, int unitID, Vec2 targetPos)
{
    auto hero = m_HeroList.find(unitID);
    if (hero == m_HeroList.end())
    {
        return;
    }

    if (hero->second->GetHeroType() == HERO_LAPHINX)
    {
        auto meteorSKill = dynamic_cast<MeteorSkill*>(hero->second->GetSkill(SKILL_R));
        meteorSKill->MakeMeteor(targetPos);
    }
}

