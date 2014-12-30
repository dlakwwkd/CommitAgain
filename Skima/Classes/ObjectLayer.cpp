#include "pch.h"
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
#include "MapLayer.h"
#include "MeteorSkill.h"
#include "SimpleAudioEngine.h"
#include "Item.h"
#include "Buff.h"

using namespace CocosDenshion;

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
    for (auto& unit : m_UnitList)
    {
        unit.second->Movement();
        unit.second->GetCenterSprite()->setZOrder(-unit.second->GetCenterSprite()->getPosition().y);
    }
}
//////////////////////////////////////////////////////////////////////////

void ObjectLayer::CreateHero(int playerID, int unitID, Vec2 location, Team team, RoomType roomType)
{
    std::shared_ptr<Hero> hero;
    switch (GET_SIDE_TYPE(unitID))
    {
    case HERO_MAGICIAN:	hero = std::make_shared<Magician>(location, 1.0f);	break;
    case HERO_JUPITER:	hero = std::make_shared<Jupiter>(location, 1.0f);	break;
    case HERO_LAPHINX:	hero = std::make_shared<Laphinx>(location, 1.0f);   break;
    default:
        return;
    }
    hero->SetPlayerID(playerID);
    hero->SetUnitID(unitID);
    if (playerID == TcpClient::getInstance()->getLoginId())
    {
        m_Hero = hero;
        hero->SetMyHpBar();
        GET_UI_LAYER->UpdateHpBar(hero->GetCurHp(), hero->GetMaxHp());
        hero->SetSkillSprite();
    }
    else
    {
        switch (roomType)
        {
        case ROOM_NONE:
            break;
        case ROOM_MELEE:
            hero->SetEnemyHpBar();
            break;
        case ROOM_TEAM:
            if (team == TcpClient::getInstance()->getTeam())
                hero->SetTeamHpBar();
            else
                hero->SetEnemyHpBar();
            break;
        default:
            break;
        }
    }
    m_UnitList[unitID] = hero;
    m_HeroList[unitID] = hero;
    this->addChild(hero->GetCenterSprite());
}

void ObjectLayer::CreateMapObject(int unitID, Vec2 pos)
{
    std::shared_ptr<MapObject> obj;
    switch (GET_SIDE_TYPE(unitID))
    {
    case OS_ROCK:       m_UnitList[unitID] =    obj = std::make_shared<Rock>(unitID, pos);       break;
    case OS_MOVE_ROCK:  m_UnitList[unitID] =    obj = std::make_shared<MoveRock>(unitID, pos);   break;
    case OS_LAVA:
        obj = std::make_shared<Lava>(unitID, pos);
        obj->SetUnitID(unitID);
        GET_MAP_LAYER->addChild(obj->GetCenterSprite());
        return;
    default:
        break;
    }
    obj->SetUnitID(unitID);

    this->addChild(obj->GetCenterSprite());
}

void ObjectLayer::CreateMob(int playerID, int unitID, Vec2 location, int hp, float speed)
{
    std::shared_ptr<Mob> unit;
    switch (GET_SIDE_TYPE(unitID))
    {
    case MOB_PEA:	unit = std::make_shared<Mob>(location, 1.0f, hp, speed);	break;
    default:
        return;
    }
    unit->SetPlayerID(playerID);
    unit->SetUnitID(unitID);
    unit->SetUnitHpBar();

    m_UnitList[unitID] = unit;
    this->addChild(unit->GetCenterSprite());
}

void ObjectLayer::CreateItem(int playerID, int unitID, Vec2 location, BuffTarget buffType)
{
    std::shared_ptr<Item> unit;
    switch (GET_SIDE_TYPE(unitID))
    {
    case ITEM_NORMAL:	unit = std::make_shared<Item>(location, 1.0f, buffType);	break;
    default:
        return;
    }
    unit->SetPlayerID(playerID);
    unit->SetUnitID(unitID);

    m_UnitList[unitID] = unit;
    this->addChild(unit->GetCenterSprite());
}

void ObjectLayer::RemoveItem(int playerID, int unitID)
{
    auto unit = m_UnitList.find(unitID);
    if (unit == m_UnitList.end())
    {
        return;
    }
    this->removeChild(unit->second->GetCenterSprite());
    m_UnitList.erase(unit);
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
    hero->second->SetTargetPos(targetPos);
    hero->second->GetCenterSprite()->stopAllActions();
    hero->second->GetRealSprite()->setVisible(true);
    hero->second->SetSkillMotionByDir(key);

    if (hero->second->GetHeroType() == HERO_LAPHINX && key == SKILL_Q && m_Hero->GetPlayerID() != playerID)
    {
        hero->second->SkillCastForEnemy(key, recvCurPos, targetPos);
    }
    else
    {
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
            SimpleAudioEngine::getInstance()->playEffect("Music/Effect/mobdied.mp3");
            this->removeChild(unit->second->GetCenterSprite());
            m_UnitList.erase(unit);
        }
            break;
        }
        return;
    }
    if (m_Hero->GetPlayerID() == playerID)
    {
        GET_UI_LAYER->UpdateHpBar(unit->second->GetCurHp(), unit->second->GetMaxHp());
    }
    unit->second->UpdateHpBar();
}

void ObjectLayer::UnitBuffApply(int unitID, float bonus, BuffTarget type, bool isOn)
{
    auto unit = m_UnitList.find(unitID);
    if (unit == m_UnitList.end())
    {
        return;
    }
    if (GET_MAIN_TYPE(unitID) != UNIT_HERO)
    {
        return;
    }
    
    auto hero = std::dynamic_pointer_cast<Hero>(unit->second);
    if (isOn)
    {
        hero->GetBuff()->BuffUse(type, bonus);
    }
    else
    {
        hero->GetBuff()->BuffEnd(type, bonus);
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
    case MS_FIRE_BALL:	missile->MissileCast("Images/Missile/fire.plist",   "Music/Effect/fireballshoot.mp3",   1000.0f, createPos, targetPos); break;
    case MS_ICE_BALL:   missile->MissileCast("Images/Missile/ice.plist",    "Music/Effect/iceballshoot.mp3",    800.0f, createPos, targetPos);  break;
    case MS_SPARK:      missile->MissileCast("Images/Missile/spark.plist",  "Music/Effect/lightningshoot.mp3",  1300.0f, createPos, targetPos); break;
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

