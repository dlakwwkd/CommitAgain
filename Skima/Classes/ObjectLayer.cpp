#include "ObjectLayer.h"
#include "PhysicsLayer.h"
#include "GameManager.h"
#include "Unit.h"


bool ObjectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_Hero = nullptr;
	createHero({ 200, 200 });

	this->schedule(schedule_selector(ObjectLayer::tick));
	return true;
}

void ObjectLayer::tick(float dt)
{
	m_Hero->movement();
	m_Hero->getSprite()->setZOrder(-m_Hero->getSprite()->getPosition().y);
	for (auto& b : m_MobList)
	{
		b->movement();
		b->getSprite()->setZOrder(-b->getSprite()->getPosition().y);
	}
}

void ObjectLayer::unitMove(Point p)
{
	if (m_Hero == nullptr) return;

	m_Hero->moveTargeting(p);

// 	auto vect = m_Hero->getBody()->getPosition();
// 	vect = GET_IM->getMouseLocation() - vect;
// 
// 	m_Hero->getBody()->setVelocity(vect);
}

void ObjectLayer::createHero(Point location)
{
	std::shared_ptr<Unit> unit(new Unit("Images/SpookyPeas.png", CIRCLE, location, 1.0f));
	m_Hero = unit;
	m_Hero->getBody()->setVelocityLimit(100);
	this->addChild(m_Hero->getSprite());
}

void ObjectLayer::addNewSpriteAtPosition(Point p)
{
	auto parent = (PhysicsLayer*)(this->getParent());
	std::shared_ptr<Unit> unit(new Unit("Images/Pea.png", CIRCLE, p - parent->getPosition(), 1.0f));
	unit->getBody()->setVelocityLimit(100);

	m_MobList.push_back(unit);
	this->addChild(unit->getSprite());
}

void ObjectLayer::MobAi()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto parent = (PhysicsLayer*)(this->getParent());

	for (auto& b : m_MobList)
	{
		if (b == m_Hero) continue;

		Vect temp;
		temp.x = rand() % (int)winSize.width;
		temp.y = rand() % (int)winSize.height;

		auto time = rand() % 300;

		if (time < 3)
			b->moveTargeting(temp);
		else if (time == 10)
			b->moveTargeting(m_Hero->getBody()->getPosition());
		else
			continue;
	}
}
