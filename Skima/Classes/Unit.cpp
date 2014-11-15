#include "pch.h"
#include "Unit.h"
#include "GameManager.h"

Unit::Unit(const std::string& filename, Point createPos, float scale)
{
	m_Speed = 10.0f;
	m_Sprite = Sprite::create(filename);
	m_Sprite->setPosition(createPos);
	m_Sprite->setScale(scale);

	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
	{
		auto material = PhysicsMaterial(1.0f, 0.6f, 0.8f); // 밀도, 탄성력, 마찰력

		m_Body = PhysicsBody::createCircle(m_Sprite->getContentSize().width*(scale / 2), material);
		m_Body->setMass(1.0f);
		m_Body->setLinearDamping(3);
		m_Body->setRotationEnable(false);

		m_Sprite->setPhysicsBody(m_Body);
		break;
	}
	case MULTI:
		break;
	}

	m_MoveState = m_StandbyState = new StandbyState();
	m_MovingState = new MovingState();
	m_CrashedState = new CrashedState();
}

Unit::~Unit()
{
	delete m_StandbyState;
	delete m_MovingState;
	delete m_CrashedState;
}



void Unit::Move()
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:	MoveS();	break;
	case MULTI:		MoveM();	break;
	}
}

void Unit::Crash()
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:	CrashS();	break;
	case MULTI:		CrashM();	break;
	}
}


///////////////////////////////////////////////////////////////////////////
/*
	게임 모드에 따라 나뉘는 함수들
*/
///////////////////////////////////////////////////////////////////////////
void Unit::MoveS()
{
// 	if (!(m_Body->getPosition().x < m_TargetPos.x - 5 ||
// 		m_Body->getPosition().y < m_TargetPos.y - 5 ||
// 		m_Body->getPosition().x > m_TargetPos.x + 5 ||
// 		m_Body->getPosition().y > m_TargetPos.y + 5))
// 	{
// 		m_MoveState->EndMove(this);
// 		m_Body->setVelocity(Vect::ZERO);
// 		return;
// 	}
// 	auto direction = m_TargetPos - m_Body->getPosition();
// 	auto temp = abs(direction.x) + abs(direction.y);
// 	direction *= m_Speed / temp;
// 
// 	m_Body->applyImpulse(direction);
}

void Unit::MoveM()
{
	auto distance = m_TargetPos - m_Sprite->getPosition();
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 300;
	auto action1 = MoveTo::create(scala, m_TargetPos);
	auto action2 = CallFunc::create(CC_CALLBACK_0(Unit::EndMove, this));
	auto action3 = Sequence::create(action1, action2, NULL);
	m_Sprite->runAction(action3);
}


void Unit::CrashS()
{

}

void Unit::CrashM()
{
	auto distance = m_TargetPos - m_Sprite->getPosition();
	auto scala = sqrt(pow(distance.x, 2) + pow(distance.y, 2)) / 200;
	auto action1 = MoveTo::create(scala, m_TargetPos);
	auto action2 = EaseSineOut::create(action1);
	m_Sprite->runAction(action2);
}


