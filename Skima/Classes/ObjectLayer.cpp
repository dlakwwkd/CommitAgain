#include "ObjectLayer.h"
#include "PhysicsLayer.h"
#include "GameManager.h"
#include "Unit.h"
#include "..\..\PacketType.h"
#include "Enums.h"


bool ObjectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_Hero = nullptr;
	
	
	//createHero({ 200, 200 });



	this->schedule(schedule_selector(ObjectLayer::Tick));
	return true;
}

//////////////////////////////////////////////////////////////////////////
void ObjectLayer::Tick(float dt)
{
	if (m_Hero == nullptr)
	{
		return;
	}
	

// 	m_Hero->Movement();
// 	m_Hero->GetSprite()->setZOrder(-m_Hero->GetSprite()->getPosition().y);
// 	for (auto& b : m_MobList)
// 	{
// 		b->Movement();
// 		b->GetSprite()->setZOrder(-b->GetSprite()->getPosition().y);
// 	}
}
//////////////////////////////////////////////////////////////////////////

void ObjectLayer::UnitMove(Point p)
{
	if (m_Hero == nullptr) return;

	m_Hero->MoveTargeting(p);

// 	auto vect = m_Hero->getBody()->getPosition();
// 	vect = GET_IM->getMouseLocation() - vect;
// 
// 	m_Hero->getBody()->setVelocity(vect);
}

void ObjectLayer::CreateHero(int unitID, Point location) // unitID를 넘어오는 playerID라 가정
{
	std::shared_ptr<Unit> unit(new Unit("Images/SpookyPeas.png", CIRCLE, location, 1.0f));
	
	unit->SetUnitID(unitID);
	m_HeroList.push_back(unit);
	

	//m_Hero->GetBody()->setVelocityLimit(100);
	
	this->addChild(m_Hero->GetSprite());
}

void ObjectLayer::AddNewSpriteAtPosition(Point p)
{
	auto parent = (PhysicsLayer*)(this->getParent());
	std::shared_ptr<Unit> unit(new Unit("Images/Pea.png", CIRCLE, p - parent->getPosition(), 1.0f));
	unit->GetBody()->setVelocityLimit(100);

	m_MobList.push_back(unit);
	this->addChild(unit->GetSprite());
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
			b->MoveTargeting(temp);
		else if (time == 10)
			b->MoveTargeting(m_Hero->GetBody()->getPosition());
		else
			continue;
	}
}

void ObjectLayer::FirstDrawUnit(int id, float x, float y)
{
	CreateHero(id, { x, y });


}
void ObjectLayer::UpdateAnimation(int id, float x, float y)
{
	
	//유닛을 찾고
	for (auto& unit : m_HeroList)
	{
		if (unit->GetUnitID() == id){
			unit->GetSprite()->setAnchorPoint(Point(0.5, 0.5));
			unit->GetSprite()->setPosition(Point(x, y));

			//return;
		}
	}

}






// 
// void ObjectLayer::CreateHeroStart()
// {
// 	int playerID = 1110;
// 	TcpClient::getInstance()->createRequest(150, 200, 200);
// }
