#pragma once
#include <map>
#include "PacketType.h"
#include "Enums.h"

USING_NS_CC;

class Unit;
class Hero;
class Missile;

class ObjectLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(ObjectLayer);

    std::shared_ptr<Hero> GetMyHero(){ return m_Hero; }

    void Tick(float dt);

    void CreateHero(int playerID, int unitID, Vec2 location);
    void CreateMapObject(int unitID, Vec2 pos);
    void CreateMob(int playerID, int unitID, Vec2 location, int hp, float speed);
    void CreateItem(int playerID, int unitID, Vec2 location, BuffTarget buffType);
    void RemoveItem(int playerID, int unitID);
    void UnitMove(int unitID, Vec2 recvCurPos, Vec2 targetPos);
    void UnitCrash(int unitID, Vec2 exPos);
    void UnitCrashEnd(int unitID, Vec2 revisePos);
    void UnitSkillUse(int playerID, int unitID, SkillKey key, Vec2 recvCurPos, Vec2 targetPos);
    void UnitHpUpdate(int playerID, int unitID, int curHp);
    void UnitBuffApply(int unitID, float bonus, BuffTarget type, bool isOn);

    void ShootMissile(int missileID, Vec2 createPos, Vec2 targetPos);
    void MissileCrash(int missileID);
    void DeleteMissile(int missileID);
    void UnHide(int playerID, int unitID, Vec2 recvCurPos);
    void MeteorCreate(int playerID, int unitID, Vec2 targetPos);

protected:
    std::shared_ptr<Hero>					m_Hero = nullptr;
    std::map<int, std::shared_ptr<Unit>>	m_UnitList;
    std::map<int, std::shared_ptr<Hero>>    m_HeroList;
    std::map<int, Missile*>					m_MissileList;

    std::vector<std::shared_ptr<Unit>>		m_MobList;
};
