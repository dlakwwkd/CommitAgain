#include "pch.h"
#include "Unit.h"
#include "Hero.h"
#include "Skill.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "Mob.h"
#include "Macros.h"
#include "Buff.h"
#include <memory>
using namespace CocosDenshion;


Unit::Unit()
{
    m_UnitType = UNIT_NONE;
    m_Name = "";
    m_PlayerID = -1;
    m_UnitID = -1;
    m_CurHp = m_MaxHp = 0;
    m_CooltimeBonus = 0;
    m_Speed = 0;
    m_InUse = false;
    m_IsHidden = false;
    m_TargetPos = { 0, 0 };
    m_CenterSprite = Sprite::create("Images/Unit/CloackingUnit.png");
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
    if (GET_MAIN_TYPE(m_UnitID) == UNIT_HERO)
    {
        auto hero = dynamic_cast<Hero*>(this);
        hero->SetMoveMotionByDir();
    }
    if (GET_MAIN_TYPE(m_UnitID) == UNIT_MOB)
    {
        this->SetMoveMotionByDir();
    }

    auto gap = m_TargetPos - m_CenterSprite->getPosition();
    gap.normalize();
    m_TargetPos -= gap * 15;
    auto distance = m_CenterSprite->getPosition().distance(m_TargetPos);
    auto time = distance / m_Speed;
    auto action1 = MoveTo::create(time, m_TargetPos);
    auto action2 = CallFunc::create(CC_CALLBACK_0(Unit::EndMove, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_CenterSprite->runAction(action3);
}

void Unit::Crash()
{
    auto distance = m_CenterSprite->getPosition().distance(m_TargetPos);
    auto time = sqrt(distance) / 15;
    auto action1 = MoveTo::create(time, m_TargetPos);
    auto action2 = EaseOut::create(action1, 2.5f);
    m_CenterSprite->runAction(action2);
}



void Unit::InitCenterSprite()
{
    m_CenterSprite->stopAllActions();
    m_CenterSprite->setVisible(true);
}

void Unit::InitRealSprite()
{
    m_RealSprite->stopAllActions();
    m_RealSprite->setVisible(true);
    m_RealSprite->setColor(Color3B(255, 255, 255));
}

void Unit::SetAllSpriteVisible()
{
    m_CenterSprite->setOpacity(255);
    m_RealSprite->setOpacity(255);
    m_HpBarFrame->setOpacity(255);
    if (m_HpBar != nullptr)
    {
        m_HpBar->setOpacity(255);
    }
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

void Unit::SetMyHpBar()
{
    SetHeroHpBar("Images/Interface/hp_bar_in.png");
}

void Unit::SetEnemyHpBar()
{
    SetHeroHpBar("Images/Interface/hp_bar_in_enemy.png");
}

void Unit::SetTeamHpBar()
{
    SetHeroHpBar("Images/Interface/hp_bar_in_team.png");
}

void Unit::SetUnitHpBar()
{
    m_HpBarFrame = Sprite::create("Images/Interface/hp_bar_frame_mob.png");
    m_HpBarFrame->setPosition(Vec2(0, 50));
    m_CenterSprite->addChild(m_HpBarFrame, 10);

    m_HpBar = Sprite::create("Images/Interface/hp_bar_in_mob.png");
    m_HpBar->setAnchorPoint(Vec2(0, 0));
    m_HpBar->setPosition(Vec2(2, 2));
    m_HpBarFrame->addChild(m_HpBar);
}

void Unit::UpdateHpBar()
{
    if (m_HpBar)
    {
        Damaged();
        m_HpBar->setScaleX(m_CurHp / m_MaxHp);
    }
}




void Unit::SetHeroHpBar(const char* barImage)
{
    m_HpBarFrame = Sprite::create("Images/Interface/hp_bar_frame.png");
    m_HpBarFrame->setPosition(Vec2(0, 75));
    m_CenterSprite->addChild(m_HpBarFrame, 10);

    m_HpBar = Sprite::create(barImage);
    m_HpBar->setAnchorPoint(Vec2(0, 0));
    m_HpBar->setPosition(Vec2(5, 5));
    m_HpBarFrame->addChild(m_HpBar);
}

void Unit::Damaged()
{
    if (GET_MAIN_TYPE(m_UnitID) == UNIT_HERO)
    {
        auto hero = dynamic_cast<Hero*>(this);

        if (hero->GetBuff()->GetBuffNum(BUFF_SHIELD) > 0)
        {
            SimpleAudioEngine::getInstance()->playEffect("Music/Effect/shield.mp3");

        }
    }
    {
        SimpleAudioEngine::getInstance()->playEffect("Music/Effect/damage.mp3");
    }

    auto action1 = TintTo::create(0, 255, 0, 0);
    auto action2 = TintTo::create(0.1f, 255, 255, 255);
    auto action3 = Sequence::create(action1, action2, action1, action2, action1, action2, NULL);
    

    //auto action1 = Blink::create(0.5f, 4);

    m_RealSprite->runAction(action3);
    //m_Damaged->setVisible(false);
}

Direction Unit::CalcMoveDirection(Vec2 displacement)
{
    float slope = displacement.y / displacement.x;

    if (displacement.x > 0)
    {
        if (slope > -0.41f  && slope <= 0.41f)  return Direction::E;
        if (slope > 0.41f   && slope <= 2.41f)  return Direction::NE;
        if (slope <= -0.41f && slope > -2.41f)  return Direction::SE;
        if (slope > 2.41f)                      return Direction::NE;
        if (slope <= -2.41f)                    return Direction::S;
    }
    else if (displacement.x < 0)
    {
        if (slope > -0.41f  && slope <= 0.41f)  return Direction::W;
        if (slope > 0.41f   && slope <= 2.41f)  return Direction::SW;
        if (slope <= -0.41f && slope > -2.41f)  return Direction::NW;
        if (slope > 2.41f)                      return Direction::SW;
        if (slope <= -2.41f)                    return Direction::N;
    }
    else if (displacement.x == 0)
    {
        if (displacement.y < 0)
            return Direction::S;
        else
            return Direction::N;
    }
    return Direction::E;
}

Direction Unit::CalcSkillDirection(Vec2 displacement)
{
    float slope = displacement.y / displacement.x;

    if (displacement.x > 0)
    {
        if (slope >= 0)
            return Direction::NE;
        else
            return Direction::SE;
    }
    else
    {
        if (slope >= 0)
            return Direction::SW;
        else
            return Direction::NW;
    }
    return Direction::SE;
}

RepeatForever* Unit::MakeUnitAnimation(const char* format, int size)
{
    auto animation = Animation::create();
    if (size < 5)
        animation->setDelayPerUnit(1.0f);
    
    else
        animation->setDelayPerUnit(0.3f);

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }
    return RepeatForever::create(Animate::create(animation));
}

Animate* Unit::MakeUnitAnimationOnce(const char* format, int size)
{
    auto animation = Animation::create();

    if (size < 5)
        animation->setDelayPerUnit(0.3f);
    else
        animation->setDelayPerUnit(0.3f);
   

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }

    return Animate::create(animation);
}