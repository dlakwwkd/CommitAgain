#pragma once
#include "cocos2d.h"
#include "..\..\PacketType.h"

USING_NS_CC;

class Unit;

class ObjectLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ObjectLayer);

	void Tick(float dt);

	void UnitMove(Point p);
	void AddNewSpriteAtPosition(Point p);
	void CreateHero(int playerID, int unitID, Point location);
	

	void MobAi();
	void FirstDrawUnit(int playerID, int unitID, UnitType unitType, float x, float y);

	
	void UpdateAnimation(int playerId, int unitID, float x, float y);

	
	//void CreateHeroStart();


protected:
	std::shared_ptr<Unit>				m_Hero;
	std::vector<std::shared_ptr<Unit>>	m_MobList;
	std::vector<std::shared_ptr<Unit>>	m_HeroList;

};

