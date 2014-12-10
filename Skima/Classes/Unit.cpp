#include "pch.h"
#include "Unit.h"
#include "Hero.h"
#include "Skill.h"
#include "GameManager.h"

Unit::Unit()
{
    m_Name = "";
    m_PlayerID = -1;
    m_UnitID = -1;
    m_CurHp = m_MaxHp = 0;
    m_Speed = 0;
    m_TargetPos = { 0, 0 };
    m_MyHpBar = nullptr;
    m_Body = nullptr;
    m_InUse = false;
    m_MoveState = m_StandbyState = new StandbyState();
    m_MovingState = new MovingState();
    m_CrashedState = new CrashedState();
    m_Sprite = Sprite::create("Images/CloackingUnit.png");
    m_RealSprite = nullptr;
}

Unit::~Unit()
{
    delete m_StandbyState;
    delete m_MovingState;
    delete m_CrashedState;
}

void Unit::UpdateMyHpBar()
{
    m_MyHpBar->setScaleX(m_CurHp / m_MaxHp);
}
void Unit::UpdateOtherHpBar()
{
    m_OtherHpBar->setScaleX(m_CurHp / m_MaxHp);
}
void Unit::SetHpBar()
{
    auto hpBarOut = Sprite::create("Images/hp_bar_out.png");
    hpBarOut->setPosition(Vec2(-25, 80));
    hpBarOut->setAnchorPoint(Vec2(0, 0));
    m_Sprite->addChild(hpBarOut);
    m_MyHpBar = Sprite::create("Images/hp_bar_in.png");
    m_MyHpBar->setPosition(Vec2(-20, 85));
    m_MyHpBar->setAnchorPoint(Vec2(0,0));
    m_OtherHpBar = Sprite::create("Images/hp_bar_in_enemy.png");
    m_OtherHpBar->setPosition(Vec2(-20, 85));
    m_OtherHpBar->setAnchorPoint(Vec2(0, 0));
}

void Unit::Move()
{
    switch (GET_GM.GetGameMode())
    {
    case SINGLE:    MoveS();    break;
    case MULTI:     MoveM();    break;
    }
}

void Unit::Crash()
{
    switch (GET_GM.GetGameMode())
    {
    case SINGLE:    CrashS();   break;
    case MULTI:     CrashM();   break;
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
