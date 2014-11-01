#pragma once
#include "cocos2d.h"

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
	void CreateHero(Point location);
	void MobAi();

	void FirstDrawUnit(int id, float x, float y);
	void UpdateAnimation(int id, float x, float y);
	//void CreateHeroStart();


protected:
	std::shared_ptr<Unit>				m_Hero;
	std::vector<std::shared_ptr<Unit>>	m_MobList;


};

