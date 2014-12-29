#include "pch.h"
#include "Buff.h"
#include "Hero.h"


Buff::Buff(Hero* hero)
{
    m_Owner = hero;
    auto speedSprite = Sprite::create("Images/buff_speed.png");
    BuffObject speed{ BUFF_SPEED, 0, speedSprite };
    m_BuffList[BUFF_SPEED] = speed;
//     BuffObject shield{ BUFF_SHIELD, 0, nullptr };
//     m_BuffList[BUFF_SHIELD] = shield;

    for (auto& buff : m_BuffList)
    {
        auto sprite = buff.second.mSprite;
        auto pos = hero->GetCenterSprite()->getPosition();
        sprite->setVisible(false);
        sprite->setPosition(Vec2(pos.x - 410.0f, pos.y - 490.0f));
        hero->GetCenterSprite()->addChild(sprite);
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
    if (buff->second.mBuffNum <= 0)
    {
        BuffDraw(buff->second.mSprite);
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
    case BUFF_SHIELD:
        break;
    }

    buff->second.mBuffNum--;
    if (buff->second.mBuffNum >= 0)
    {
        BuffErase(buff->second.mSprite);
    }
}

void Buff::BuffDraw(Sprite* sprite)
{
    sprite->setVisible(true);
}

void Buff::BuffErase(Sprite* sprite)
{
    sprite->setVisible(false);
}
