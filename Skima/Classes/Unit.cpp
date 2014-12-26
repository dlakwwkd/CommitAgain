﻿#include "pch.h"
#include "Unit.h"
#include "Hero.h"
#include "Skill.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


Unit::Unit()
{
    m_UnitType = UNIT_NONE;
    m_Name = "";
    m_PlayerID = -1;
    m_UnitID = -1;
    m_CurHp = m_MaxHp = 0;
    m_Speed = 0;
    m_InUse = false;
    m_IsHidden = false;
    m_TargetPos = { 0, 0 };
    m_CenterSprite = Sprite::create("Images/CloackingUnit.png");
//     m_Damaged = Sprite::create("Images/Red.png");
//     m_Damaged->setZOrder(5);
//     m_Damaged->setOpacity(80);
//     m_Damaged->setVisible(false);
    //m_RealSprite->addChild(m_Damaged);

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
    SetHeroHpBar("Images/hp_bar_in.png");
}

void Unit::SetEnemyHpBar()
{
    SetHeroHpBar("Images/hp_bar_in_enemy.png");
}

void Unit::SetUnitHpBar()
{
    m_HpBar = Sprite::create("Images/hp_bar_in_mob.png");
    m_HpBar->setPosition(Vec2(-25, 85));
    m_HpBar->setAnchorPoint(Vec2(0, 0));

    m_CenterSprite->addChild(m_HpBar, 16);
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
    m_HpBarFrame = Sprite::create("Images/hp_bar_frame.png");
    m_HpBarFrame->setPosition(Vec2(-30, 80));
    m_HpBarFrame->setAnchorPoint(Vec2(0, 0));

    m_HpBar = Sprite::create(barImage);
    m_HpBar->setPosition(Vec2(-25, 85));
    m_HpBar->setAnchorPoint(Vec2(0, 0));

    m_CenterSprite->addChild(m_HpBarFrame, 10);
    m_CenterSprite->addChild(m_HpBar, 16);
}

void Unit::Damaged()
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/damage.mp3");

//     auto action1 = TintTo::create(0.1f,0x50,0x00,0x00);
//     auto action2 = TintTo::create(0.1f, 0x00, 0x00, 0x00);
//     auto action3 = Sequence::create(action1, action2, action1, NULL);
    
    auto action1 = Blink::create(0.5f, 4);

    m_RealSprite->runAction(action1);
    //m_Damaged->setVisible(false);
}
