#include "ObjectLayer.h"
#include "PhysicsLayer.h"
#include "LoadingBGLayer.h"
#include "GameManager.h"
#include "Unit.h"
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
	if (m_Hero == nullptr) return;
	
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

void ObjectLayer::CreateHero(int playerID, int unitID, Point location) // unitID를 넘어오는 playerID라 가정
{
	//todo unitType 맹글어야함

	std::shared_ptr<Unit> unit(new Unit("Images/SpookyPeas.png", location, 1.0f, MULTI));
	
	unit->SetUnitID(unitID);
	unit->SetUnitPlayerID(playerID);
	m_HeroList.push_back(unit);
	//todo : herolist로 접근하는것 수정해야함

	//m_Hero->GetBody()->setVelocityLimit(100);
	
	this->addChild(unit->GetSprite());
}

void ObjectLayer::AddNewSpriteAtPosition(Point p)
{
	auto parent = dynamic_cast<PhysicsLayer*>(this->getParent());
	std::shared_ptr<Unit> unit(new Unit("Images/Pea.png", p - parent->getPosition(), 1.0f, SINGLE));
	//unit->GetBody()->setVelocityLimit(100);

	m_MobList.push_back(unit);
	this->addChild(unit->GetSprite());
}

void ObjectLayer::MobAi()
{
// 	auto winSize = Director::getInstance()->getWinSize();
// 	auto parent = (PhysicsLayer*)(this->getParent());
// 
// 	for (auto& b : m_MobList)
// 	{
// 		if (b == m_Hero) continue;
// 
// 		Vect temp;
// 		temp.x = rand() % (int)winSize.width;
// 		temp.y = rand() % (int)winSize.height;
// 
// 		auto time = rand() % 300;
// 
// 		if (time < 3)
// 			b->MoveTargeting(temp);
// 		else if (time == 10)
// 			b->MoveTargeting(m_Hero->GetBody()->getPosition());
// 		else
// 			continue;
// 	}
}

void ObjectLayer::FirstDrawUnit(int playerID, int unitID, UnitType unitType, Point pos)

{
	//todo unitType 넣어주기
	CreateHero(playerID, unitID, pos);
}
void ObjectLayer::UpdateAnimation(int playerId, int unitID, Point pos)
{
	//유닛을 찾고
	for (auto& unit : m_HeroList)
	{
		if (unit->GetUnitID() == unitID){
			unit->GetSprite()->setAnchorPoint(Point(0.5, 0.5));
			unit->GetSprite()->setPosition(pos);

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
