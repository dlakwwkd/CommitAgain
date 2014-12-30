#include "stdafx.h"
#include "BuffType.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Timer.h"


BuffType::BuffType()
{
    m_Duration = 0;
    m_SpeedBonus = 0;
}


BuffType::~BuffType()
{
}

void BuffType::DashSkillCast()
{
    if (!m_IsOn)
    {
        m_IsOn = true;
        auto hero = m_Owner->GetMyHero();
        if (hero == nullptr)
        {
            return;
        }
        hero->SetSpeed(hero->GetSpeed() + m_SpeedBonus);
        hero->SetDamage(hero->GetDamage() + m_Damage);

        auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
        auto func = std::bind(&BuffType::DashSkillEnd, this);
        auto timer = new Timer(m_Owner->GetRoomID());
        timer->CallFuncOnce(m_Duration, func);
        game->PushTimer(timer);

        auto client = m_Owner->GetClient();
        client->BuffBroadCast(hero->GetUnitID(), m_SpeedBonus, BUFF_SPEED, m_IsOn);
    }
}

void BuffType::DashSkillEnd()
{
    if (m_IsOn)
    {
        m_IsOn = false;
        auto hero = m_Owner->GetMyHero();
        if (hero == nullptr)
        {
            return;
        }
        hero->SetSpeed(hero->GetSpeed() - m_SpeedBonus);
        hero->SetDamage(hero->GetDamage() - m_Damage);
        hero->EndMove();
        hero->CurPosSync();

        auto client = m_Owner->GetClient();
        client->BuffBroadCast(hero->GetUnitID(), (-m_SpeedBonus), BUFF_SPEED, m_IsOn);
    }
}


void BuffType::MoveSpeedBonus(int duration, float bonus)
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }
    hero->SetSpeed(hero->GetSpeed() + bonus);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&BuffType::MoveSpeedBonusEnd, this, bonus);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->CallFuncOnce(duration, func);
    game->PushTimer(timer);

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), bonus, BUFF_SPEED, true);
}

void BuffType::MoveSpeedBonusEnd(float bonus)
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }
    hero->SetSpeed(hero->GetSpeed() - bonus);

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), (-bonus), BUFF_SPEED, false);
}

void BuffType::DamageUpBonus(int duration, int bonus)
{

}

void BuffType::DamageUpBonusEnd(int bonus)
{

}

void BuffType::ShieldBonus(int bonus)
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }
    hero->SetShield(hero->GetShield() + bonus);

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), 0, BUFF_SHIELD, true);
}

void BuffType::ShieldBonusEnd()
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), 0, BUFF_SHIELD, false);
}

void BuffType::HpBonus(int bonus)
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }
    int hp = hero->GetHp() + bonus;
    if (hp > hero->GetMaxHp())
    {
        hp = hero->GetMaxHp();
    }
    hero->SetHp(hp);

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), 0, BUFF_HP, true);
    client->HpBroadCast(m_Owner->GetPlayerID(), hero->GetUnitID(), hero->GetHp());
}

void BuffType::DamageBonus(int duration, int bonus)
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }
    hero->SetDamageBonus(hero->GetDamageBonus() + bonus);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&BuffType::DamageBonusEnd, this, bonus);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->CallFuncOnce(duration, func);
    game->PushTimer(timer);

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), 0, BUFF_DAMAGE, true);
}

void BuffType::DamageBonusEnd(int bonus)
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }
    hero->SetDamageBonus(hero->GetDamageBonus() - bonus);

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), 0, BUFF_DAMAGE, false);
}

void BuffType::CooltimeBonus(int duration, float bonus)
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&BuffType::CooltimeBonumEnd, this, bonus);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->CallFuncOnce(duration, func);
    game->PushTimer(timer);

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), bonus, BUFF_COOLTIME, true);
}

void BuffType::CooltimeBonumEnd(float bonus)
{
    auto hero = m_Owner->GetMyHero();
    if (hero == nullptr)
    {
        return;
    }

    auto client = m_Owner->GetClient();
    client->BuffBroadCast(hero->GetUnitID(), (-bonus), BUFF_COOLTIME, false);
}
