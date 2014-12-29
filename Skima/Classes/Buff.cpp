#include "pch.h"
#include "Buff.h"
#include "Hero.h"


Buff::Buff(Hero* hero)
{
    m_Owner = hero;

    auto speedParticle = ParticleSystemQuad::create("Images/Effect/Particle_Speed_Buff.plist");
    BuffObject speed{ BUFF_SPEED, 0, nullptr, speedParticle };
    m_BuffList[BUFF_SPEED] = speed;

    auto shieldSprite = Sprite::create("Images/Effect/buff_shield.png");
    BuffObject shield{ BUFF_SHIELD, 0, shieldSprite, nullptr };
    m_BuffList[BUFF_SHIELD] = shield;

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
            hero->GetCenterSprite()->addChild(speedParticle, -1);
        }
        
    }
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
    if (buff->second.mBuffNum == 0)
    {
        BuffDraw(&buff->second);
    }
    buff->second.mBuffNum++;

    switch (type)
    {
    case BUFF_HP:       
        m_Owner->SetHp(m_Owner->GetCurHp() + bonus);      
        break;
    case BUFF_SPEED:    
        m_Owner->SetSpeed(m_Owner->GetSpeed() + bonus);
        break;
    case BUFF_SHIELD:   
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
    }

    buff->second.mBuffNum--;
    if (buff->second.mBuffNum == 0)
    {
        BuffErase(&buff->second);
    }
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
