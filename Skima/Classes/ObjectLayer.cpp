#include "pch.h"
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

	return true;
}

//////////////////////////////////////////////////////////////////////////
void ObjectLayer::TickS(float dt)
{
	if (m_Hero == nullptr) return;
	
	m_Hero->Move();
	m_Hero->GetSprite()->setZOrder(-m_Hero->GetSprite()->getPosition().y);
	for (auto& b : m_MobList)
	{
		b->Move();
		b->GetSprite()->setZOrder(-b->GetSprite()->getPosition().y);
	}
}
void ObjectLayer::TickM(float dt)
{
// 	for (auto& unit : m_UnitList)
// 	{
// 		unit.second->Movement();
// 	}
}
//////////////////////////////////////////////////////////////////////////



void ObjectLayer::CreateHero(int playerID, int unitID, Point location) // unitID를 넘어오는 playerID라 가정
{
	//todo unitType 맹글어야함

	std::shared_ptr<Unit> unit(new Unit("Images/SpookyPeas.png", location, 1.0f));

	unit->SetUnitID(unitID);
	unit->SetUnitPlayerID(playerID);
	m_UnitList[unitID] = unit;

	if (playerID == TcpClient::getInstance()->getLoginId())
	{
		m_Hero = unit;
	}

	//m_Hero->GetBody()->setVelocityLimit(100);

	this->addChild(unit->GetSprite());
}

void ObjectLayer::UnitMove(int unitID, Point recvCurPos, Point targetPos)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		UnitMoveS(targetPos);
		break;
	case MULTI:
		UnitMoveM(unitID, recvCurPos, targetPos);

// 		for (auto& unit : m_UnitList)
// 		{
// 			if (unit->GetUnitID() == unitID)
// 			{
// 				//FSM체크하고
// 				//현재위치랑 보내준위치랑 체크해서 일정범위안이면 moveM움직이도록 // 범위밖이면.....T.T
// 				if (PosGapCheck(unit, recvCurPos) == true)
// 				{
// 					
// 				}
// 			}
// 		}
		break;
	}
}

void ObjectLayer::UnitCrash(int unitID, Point recvPos)
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
		UnitCrashS(recvPos);
		break;
	case MULTI:
		UnitCrashM(unitID, recvPos);
		break;
	}
}

void ObjectLayer::UnitCrashEnd(int unitID, Point revisePos)
{
	m_Hero->SetMoveTargetPos(revisePos);
	m_UnitList[unitID]->EndCrash();
}



void ObjectLayer::FirstDrawUnit(int playerID, int unitID, UnitType unitType, Point pos)

{
	//todo unitType 넣어주기
	CreateHero(playerID, unitID, pos);
}
void ObjectLayer::UpdateAnimation(int playerId, int unitID, Point pos)
{
	for (auto& unit : m_UnitList)
	{
		if (unit.second->GetUnitID() == unitID)
		{
			unit.second->GetSprite()->setAnchorPoint(Point(0.5, 0.5));
			unit.second->GetSprite()->setPosition(pos);
			
		}
	}
}



void ObjectLayer::AddNewSpriteAtPosition(Point pos)
{
	auto parent = dynamic_cast<PhysicsLayer*>(this->getParent());
	std::shared_ptr<Unit> unit(new Unit("Images/Pea.png", pos - parent->getPosition(), 1.0f));
	unit->GetBody()->setVelocityLimit(100);

	m_MobList.push_back(unit);
	this->addChild(unit->GetSprite());
}

void ObjectLayer::MobAi()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto parent = dynamic_cast<PhysicsLayer*>(this->getParent());

	for (auto& b : m_MobList)
	{
		if (b == m_Hero) continue;

		Vect temp;
		temp.x = rand() % (int)winSize.width;
		temp.y = rand() % (int)winSize.height;

		auto time = rand() % 300;

		if (time < 3)
			b->SetMoveTargetPos(temp);
		else if (time == 10)
			b->SetMoveTargetPos(m_Hero->GetBody()->getPosition());
		else
			continue;
	}
}


bool ObjectLayer::PosGapCheck(std::shared_ptr<Unit> unit, Point recvCurPos)
{
	Point unitPos = unit->GetSprite()->getPosition();

	if (unitPos.x - recvCurPos.x > 5 || unitPos.x - recvCurPos.x<-5)
		return false;

	if (unitPos.y - recvCurPos.y>5 || unitPos.y - recvCurPos.y < -5)
		return false;

	else
		return true;
}



///////////////////////////////////////////////////////////////////////////
/*
	게임 모드에 따라 나뉘는 함수들
*/
///////////////////////////////////////////////////////////////////////////
void ObjectLayer::UnitMoveS(Point pos)
{
	m_Hero->SetMoveTargetPos(pos);
	m_Hero->TryMove();

// 	auto vect = m_Hero->GetBody()->getPosition();
// 	vect = GET_IM->GetMouseLocation() - vect;
// 
// 	m_Hero->GetBody()->setVelocity(vect);
}
void ObjectLayer::UnitMoveM(int unitID, Point recvCurPos, Point targetPos)
{
	m_UnitList[unitID]->SetMoveTargetPos(targetPos);
	m_UnitList[unitID]->TryMove();
}


void ObjectLayer::UnitCrashS(Point pos)
{

}

void ObjectLayer::UnitCrashM(int unitID, Point recvPos)
{
	m_UnitList[unitID]->SetMoveTargetPos(recvPos);
	m_UnitList[unitID]->Crashed();
}




