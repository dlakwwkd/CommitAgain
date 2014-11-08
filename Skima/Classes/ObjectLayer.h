#pragma once
#include "cocos2d.h"
#include "../../PacketType.h"
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

	void CreateHero(int playerID, int unitID, Point location);
	void UnitMove(int unitID, Point recvCurPos, Point targetPos, GameMode gameMode);
	bool PosGapCheck(std::shared_ptr<Unit> unit, Point recvCurPos);
	void FirstDrawUnit(int playerID, int unitID, UnitType unitType, Point pos);
	void UpdateAnimation(int playerId, int unitID, Point pos);

	void AddNewSpriteAtPosition(Point pos);
	void MobAi();

protected:
	void UnitMoveS(Point pos);
	void UnitMoveM(Point pos);

protected:
	std::shared_ptr<Unit>				m_Hero;
	std::vector<std::shared_ptr<Unit>>	m_MobList;
	std::vector<std::shared_ptr<Unit>>	m_UnitList;

};

