#pragma once
#include <map>
#include "PacketType.h"
#include "Enums.h"

USING_NS_CC;

class Unit;

class ObjectLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ObjectLayer);

	void TickS(float dt);
	void TickM(float dt);

	std::shared_ptr<Unit> GetMyHero(){ return m_Hero; }

	void CreateHero(int playerID, int unitID, Point location, HeroType heroType);
	void UnitMove(int unitID, Point recvCurPos, Point targetPos);
	void UnitCrash(int unitID, Point recvPos);
	void UnitCrashEnd(int unitID, Point revisePos);
	void UnitSkillUse(int unitID, SkillKey key, Point recvCurPos, Point targetPos);

	void FirstDrawUnit(int playerID, int unitID, HeroType heroType, Point pos);

// 	void AddNewSpriteAtPosition(Point pos);
// 	void MobAi();

protected:
	void UnitMoveS(Point pos);
	void UnitMoveM(int unitID, Point recvCurPos, Point targetPos);
	void UnitCrashS(Point pos);
	void UnitCrashM(int unitID, Point recvPos);
	void UnitSkillUseS(SkillKey key, Point pos);
	void UnitSkillUseM(int unitID, SkillKey key, Point recvCurPos, Point targetPos);

protected:
	std::shared_ptr<Unit>					m_Hero;
	std::map<int, std::shared_ptr<Unit>>	m_UnitList;


	std::vector<std::shared_ptr<Unit>>		m_MobList;

};

