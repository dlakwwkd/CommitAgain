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

    void TickS(float dt);
    void TickM(float dt);

    std::shared_ptr<Hero> GetMyHero(){ return m_Hero; }

    void CreateHero(int playerID, int unitID, Vec2 location);
    void UnitMove(int unitID, Vec2 recvCurPos, Vec2 targetPos);
    void UnitCrash(int unitID, Vec2 exPos);
    void UnitCrashEnd(int unitID, Vec2 revisePos);
    void UnitSkillUse(int unitID, SkillType type, SkillKey key, Vec2 recvCurPos, Vec2 targetPos);
    void UnitHpUpdate(int playerID, int unitID, int curHp);

    void ShootMissile(int missileID, Vec2 createPos, Vec2 targetPos);
    void MissileCrash(int missileID);
    void DeleteMissile(int missileID);

// 	void AddNewSpriteAtPosition(Point pos);
// 	void MobAi();

protected:
    void UnitMoveS(Vec2 pos);
    void UnitMoveM(int unitID, Vec2 recvCurPos, Vec2 targetPos);
    void UnitCrashS(Vec2 pos);
    void UnitCrashM(int unitID, Vec2 exPos);
    void UnitSkillUseS(SkillKey key, Vec2 pos);
    void UnitSkillUseM(int unitID, SkillType type, SkillKey key, Vec2 recvCurPos, Vec2 targetPos);
    void ShootMissileS(Vec2 createPos, Vec2 targetPos);
    void ShootMissileM(int missileID, Vec2 createPos, Vec2 targetPos);
    void MissileCrashS();
    void MissileCrashM(int missileID);
    void UnitHpUpdateS(int curHp);
    void UnitHpUpdateM(int playerID, int unitID, float curHP);


protected:
    std::shared_ptr<Hero>					m_Hero;
    std::map<int, std::shared_ptr<Unit>>	m_UnitList;
    std::map<int, std::shared_ptr<Hero>>    m_HeroList;
    //std::map<int, std::shared_ptr<Missile>>	m_MissileList;
    std::map<int, Missile*>	m_MissileList;


    std::vector<std::shared_ptr<Unit>>		m_MobList;
};

