﻿#include "pch.h"
#include "Buff.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;


Buff::Buff(Hero* hero)
{
    m_Owner = hero;

    auto speedParticle = ParticleSystemQuad::create("Images/Effect/Particle_Speed_Buff.plist");
    BuffObject speed{ BUFF_SPEED, 0, nullptr, speedParticle };
    m_BuffList[BUFF_SPEED] = speed;

    auto shieldSprite = Sprite::create("Images/Effect/buff_shield.png");
    BuffObject shield{ BUFF_SHIELD, 0, shieldSprite, nullptr };
    m_BuffList[BUFF_SHIELD] = shield;

    BuffObject hp{ BUFF_HP, 0, nullptr, nullptr };
    m_BuffList[BUFF_HP] = hp;

    auto damageParticle = ParticleSystemQuad::create("Images/Effect/particle_damage_buff.plist");
    BuffObject damage{ BUFF_DAMAGE, 0, nullptr, damageParticle };
    m_BuffList[BUFF_DAMAGE] = damage;

    auto cooltimeParticle = ParticleSystemQuad::create("Images/Effect/particle_cooltime_buff.plist");
    BuffObject cooltime{ BUFF_COOLTIME, 0, nullptr, cooltimeParticle };
    m_BuffList[BUFF_COOLTIME] = cooltime;

    for (auto& buff : m_BuffList)
    {
        auto sprite = buff.second.mSprite;
        auto particle = buff.second.mParticle;

        if (sprite != nullptr)
        {
            sprite->setVisible(false);
            sprite->setScaleX(0.8f);
            sprite->setScaleY(0.6f);
            hero->GetCenterSprite()->addChild(sprite);
        }

        if (particle != nullptr)
        {
            particle->setVisible(false);
            particle->setPosition(Vec2::ZERO);
            particle->setScale(0.5f);
            hero->GetCenterSprite()->addChild(particle, -1);
        }
        
    }

    damageParticle->setScale(0.8f);
}


Buff::~Buff()
{
    
}

void Buff::BuffUse(BuffTarget type, float bonus)
{

    auto buff = m_BuffList.find(type);
    if (buff == m_BuffList.end())
    {
        return;
    }
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/buff_on.mp3");


    if (buff->second.mBuffNum == 0)
    {
        BuffDraw(&buff->second);
    }
    buff->second.mBuffNum++;

    switch (type)
    {
    case BUFF_HP:
        HpBuffEffect();
        break;
    case BUFF_SPEED:    
        m_Owner->SetSpeed(m_Owner->GetSpeed() + bonus);
        break;
    case BUFF_COOLTIME: 
        m_Owner->SetCooltimeBonus(m_Owner->GetCooltimeBonus() + bonus);
        break;
    }
}

void Buff::BuffEnd(BuffTarget type, float bonus)
{
    auto buff = m_BuffList.find(type);
    if (buff == m_BuffList.end())
    {
        return;
    }

    switch (type)
    {
    case BUFF_SPEED:
        m_Owner->SetSpeed(m_Owner->GetSpeed() + bonus);
        break;
    case BUFF_SHIELD:
        buff->second.mBuffNum = 1;
        SimpleAudioEngine::getInstance()->playEffect("Music/Effect/shield_off.mp3");

        break;
    case BUFF_COOLTIME:
        m_Owner->SetCooltimeBonus(m_Owner->GetCooltimeBonus() + bonus);
        break;
    }

    buff->second.mBuffNum--;
    if (buff->second.mBuffNum == 0)
    {
        BuffErase(&buff->second);
    }
}

int Buff::GetBuffNum(BuffTarget type)
{
    auto buff = m_BuffList.find(type);
    if (buff == m_BuffList.end())
    {
        return -1;
    }
    return buff->second.mBuffNum;
}


void Buff::BuffDraw(BuffObject* buff)
{
    if (buff->mSprite != nullptr)
    {
        buff->mSprite->setVisible(true);
    }

    if (buff->mParticle != nullptr)
    {
        buff->mParticle->setVisible(true);
    }
}

void Buff::BuffErase(BuffObject* buff)
{
    if (buff->mSprite != nullptr)
    {
        buff->mSprite->setVisible(false);
    }

    if (buff->mParticle != nullptr)
    {
        buff->mParticle->setVisible(false);
    }
}

void Buff::HpBuffEffect()
{
    m_HpParticle = ParticleSystemQuad::create("Images/Effect/particle_hp_buff.plist");
    m_HpParticle->setPosition(Vec2::ZERO);
    m_HpParticle->setScale(0.3f);
    auto action1 = DelayTime::create(2.0f);
    auto action2 = CallFunc::create(CC_CALLBACK_0(Buff::RemoveEffect, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_HpParticle->runAction(action3);
    m_Owner->GetCenterSprite()->addChild(m_HpParticle, 20);
}

void Buff::RemoveEffect()
{
    m_Owner->GetCenterSprite()->removeChild(m_HpParticle, true);
}
