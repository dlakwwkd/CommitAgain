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
    this->SetMoveMotionByDir();

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




void Unit::InitSprite()
{
    m_CenterSprite->stopAllActions();
    if (m_RealSprite)
    {
        m_RealSprite->stopAllActions();
        m_RealSprite->setColor(Color3B(255, 255, 255));
    }
}

void Unit::SetAllSpriteOpacity(GLubyte value)
{
    for (auto& sprite : m_CenterSprite->getChildren())
    {
        sprite->setOpacity(value);
    }
}



void Unit::SetName(const std::string& name)
{
	m_Name = name;

	auto label = Label::create(m_Name, "Arial", 25);
	label->setPosition(Vec2(0, 100.0f));
	m_CenterSprite->addChild(label);
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
    m_CenterSprite->addChild(m_HpBarFrame, 9);

    m_HpBar = Sprite::create("Images/Interface/hp_bar_in_mob.png");
    m_HpBar->setAnchorPoint(Vec2(0, 0.5f));
    m_HpBar->setPosition(Vec2(-36, 50));
    m_CenterSprite->addChild(m_HpBar, 10);
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
    m_CenterSprite->addChild(m_HpBarFrame, 9);

    m_HpBar = Sprite::create(barImage);
    m_HpBar->setAnchorPoint(Vec2(0, 0.5f));
    m_HpBar->setPosition(Vec2(-50, 74));
    m_CenterSprite->addChild(m_HpBar, 10);
}

void Unit::Damaged()
{
    if (GET_MAIN_TYPE(m_UnitID) == UNIT_HERO)
    {
        auto hero = dynamic_cast<Hero*>(this);
        if (hero->GetBuff()->GetBuffNum(BUFF_SHIELD) > 0)
            SimpleAudioEngine::getInstance()->playEffect("Music/Effect/shield.mp3");
    }
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/damage.mp3");

    auto action1 = TintTo::create(0, 255, 0, 0);
    auto action2 = TintTo::create(0.1f, 255, 255, 255);
    auto action3 = Sequence::create(action1, action2, action1, action2, action1, action2, NULL);
    
    m_RealSprite->runAction(action3);
}




Animate* Unit::MakeAnimationOnce(const char* format, int size, float delay)
{
    auto animation = Animation::create();
    animation->setDelayPerUnit(delay);

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }

    return Animate::create(animation);
}

RepeatForever* Unit::MakeAnimation(const char* format, int size, float delay)
{
    return RepeatForever::create(MakeAnimationOnce(format, size, delay));
}

Direction Unit::CalcMoveDirection(Vec2 displacement)
{
    float slope = displacement.y / displacement.x;

    if (displacement.x > 0)
    {
        if (slope > -0.41f  && slope <= 0.41f)      return Direction::E;
        else if (slope > 0.41f   && slope <= 2.41f) return Direction::NE;
        else if (slope <= -0.41f && slope > -2.41f) return Direction::SE;
        else if (slope > 2.41f)                     return Direction::NE;
        else                                        return Direction::S;
    }
    else if (displacement.x < 0)
    {
        if (slope > -0.41f  && slope <= 0.41f)      return Direction::W;
        else if (slope > 0.41f   && slope <= 2.41f) return Direction::SW;
        else if (slope <= -0.41f && slope > -2.41f) return Direction::NW;
        else if (slope > 2.41f)                     return Direction::SW;
        else                                        return Direction::N;
    }
    else
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
