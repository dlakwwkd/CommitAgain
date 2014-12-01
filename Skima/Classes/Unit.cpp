#include "pch.h"
#include "Unit.h"
#include "Hero.h"
#include "GameManager.h"

Unit::Unit()
{
	m_Name = "";
	m_PlayerID = -1;
	m_UnitID = -1;
	m_CurHp = m_MaxHp = 0;
	m_Speed = 0;
	m_TargetPos = { 0, 0 };
	m_Sprite = nullptr;
	m_HpBar = nullptr;
	m_Body = nullptr;
	m_InUse = false;

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

void Unit::UpdateHpBar()
{
	m_HpBar->setScaleX(m_CurHp / m_MaxHp);
}

void Unit::SetHpBar()
{
	m_HpBar = Sprite::create("Images/HpBar_Unit.png");
	m_HpBar->setPosition(Vec2(-20, 85));
	m_HpBar->setAnchorPoint(Vec2(0,0));
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

void Unit::Teleport()
{
	switch (GET_GM.GetGameMode())
	{
	case SINGLE:	TeleportS();	break;
	case MULTI:		TeleportM();	break;
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
	auto hero = dynamic_cast<Hero*>(this);
    hero->SetMoveMotionByDir();
    auto gap = m_TargetPos - m_Sprite->getPosition();
    gap.normalize();
    m_TargetPos -= gap * 15;
    auto distance = m_Sprite->getPosition().distance(m_TargetPos);
	auto time = distance / m_Speed;
    auto action1 = MoveTo::create(time, m_TargetPos);
	auto action2 = CallFunc::create(CC_CALLBACK_0(Unit::EndMove, this));
	auto action3 = Sequence::create(action1, action2, NULL);
	m_Sprite->runAction(action3);
}

void Unit::CrashS()
{

}

void Unit::CrashM()
{
    auto distance = m_Sprite->getPosition().distance(m_TargetPos);
    auto time = sqrt(distance) / 15;
    auto action1 = MoveTo::create(time, m_TargetPos);
	auto action2 = EaseOut::create(action1, 2.5f);
	m_Sprite->runAction(action2);
}

void Unit::SetHp(int curHp)
{
	if (curHp <= 0)
	{
		m_CurHp = 0;
		return;
	}
	m_CurHp = curHp;
}

void Unit::TeleportS()
{
	
}

void Unit::TeleportM()
{
	//SetMoveMotionByDir(); // test
	auto action1 = MoveTo::create(0.0f, m_TargetPos);  // another : CALLFUNC로 m_Sprite->setPosition(m_TargetPos); 하는 함수
//	auto action2 = CALLFUNC로 hero의 m_teleportparticle시전



}
