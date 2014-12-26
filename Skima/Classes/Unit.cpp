#include "pch.h"
#include "Unit.h"
#include "Hero.h"
#include "Skill.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

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
    m_UnitType = UNIT_NONE;
    m_IsHidden = false;
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

void Unit::UpdateMyHpBar()
{
    if (m_MyHpBar)
    {
        SimpleAudioEngine::getInstance()->playEffect("Music/Effect/damage.mp3");
        m_MyHpBar->setScaleX(m_CurHp / m_MaxHp);
    }
}

void Unit::UpdateOtherHpBar()
{
    if (m_EnemyHpBar)
    {
        SimpleAudioEngine::getInstance()->playEffect("Music/Effect/damage.mp3");
        m_EnemyHpBar->setScaleX(m_CurHp / m_MaxHp);
    }
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
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/crash.mp3");

    auto distance = m_Sprite->getPosition().distance(m_TargetPos);
    auto time = sqrt(distance) / 15;
    auto action1 = MoveTo::create(time, m_TargetPos);
    auto action2 = EaseOut::create(action1, 2.5f);
    m_Sprite->runAction(action2);
}

void Unit::SetAllSpriteVisible()
{
    m_Sprite->setOpacity(255);
    m_RealSprite->setOpacity(255);
    m_HpbarOut->setOpacity(255);
    if (m_MyHpBar != nullptr)
    {
        m_MyHpBar->setOpacity(255);
    }
    if (m_EnemyHpBar != nullptr)
    {
        m_EnemyHpBar->setOpacity(255);
    }
}

void Unit::SetMyHpBar()
{
    m_HpbarOut = Sprite::create("Images/hp_bar_out.png");
    m_HpbarOut->setPosition(Vec2(-30, 80));
    m_HpbarOut->setAnchorPoint(Vec2(0, 0));
    m_Sprite->addChild(m_HpbarOut, 10);
    m_MyHpBar = Sprite::create("Images/hp_bar_in.png");
    m_MyHpBar->setPosition(Vec2(-25, 85));
    m_MyHpBar->setAnchorPoint(Vec2(0, 0));
    m_Sprite->addChild(m_MyHpBar, 16);
}

void Unit::SetEnemyHpBar()
{
    m_HpbarOut = Sprite::create("Images/hp_bar_out.png");
    m_HpbarOut->setPosition(Vec2(-30, 80));
    m_HpbarOut->setAnchorPoint(Vec2(0, 0));
    m_Sprite->addChild(m_HpbarOut, 10);
    m_EnemyHpBar = Sprite::create("Images/hp_bar_in_enemy.png");
    m_EnemyHpBar->setPosition(Vec2(-25, 85));
    m_EnemyHpBar->setAnchorPoint(Vec2(0, 0));
    m_Sprite->addChild(m_EnemyHpBar, 16);
}
