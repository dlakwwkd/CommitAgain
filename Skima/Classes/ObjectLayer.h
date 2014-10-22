#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Unit;

class ObjectLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ObjectLayer);

	void tick(float dt);

	void unitMove(Point p);
	void addNewSpriteAtPosition(Point p);
	void createHero(Point location);
	void MobAi();


protected:
	std::shared_ptr<Unit>				m_Hero;
	std::vector<std::shared_ptr<Unit>>	m_MobList;


};

