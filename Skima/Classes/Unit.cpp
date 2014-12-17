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
	m_InUse = false;
	m_Sprite = Sprite::create("Images/CloackingUnit.png");
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

void Unit::SetHp(int curHp)
{
	if (curHp <= 0)
	{
		m_CurHp = 0;
		return;
	}
	m_CurHp = curHp;
}

void Unit::SetHpBar()
{
    auto hpBarOut = Sprite::create("Images/hp_bar_out.png");
    hpBarOut->setPosition(Vec2(-30, 80));
    hpBarOut->setAnchorPoint(Vec2(0, 0));
    m_Sprite->addChild(hpBarOut, 10);
    m_MyHpBar = Sprite::create("Images/hp_bar_in.png");
    m_MyHpBar->setPosition(Vec2(-25, 85));
	m_MyHpBar->setAnchorPoint(Vec2(0, 0));
    m_OtherHpBar = Sprite::create("Images/hp_bar_in_enemy.png");
    m_OtherHpBar->setPosition(Vec2(-25, 85));
    m_OtherHpBar->setAnchorPoint(Vec2(0, 0));
}

void Unit::UpdateMyHpBar()
{
	m_MyHpBar->setScaleX(m_CurHp / m_MaxHp);
}

void Unit::UpdateOtherHpBar()
{
	m_OtherHpBar->setScaleX(m_CurHp / m_MaxHp);
}

void Unit::Move()
{
	if (GET_MAIN_TYPE(m_UnitID) == UNIT_HERO)
	{
		auto hero = dynamic_cast<Hero*>(this);
		hero->SetMoveMotionByDir();
	}

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

void Unit::Crash()
{
	auto distance = m_Sprite->getPosition().distance(m_TargetPos);
	auto time = sqrt(distance) / 15;
	auto action1 = MoveTo::create(time, m_TargetPos);
	auto action2 = EaseOut::create(action1, 2.5f);
	m_Sprite->runAction(action2);
}
