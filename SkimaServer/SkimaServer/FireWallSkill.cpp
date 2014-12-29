#include "stdafx.h"
#include "FireWallSkill.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"


FireWallSkill::FireWallSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 75;
}


FireWallSkill::~FireWallSkill()
{
}

void FireWallSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

    auto direction = GenerateWalldirection(heroPos, targetPos);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&FireWallSkill::WallFieldDamage, this, targetPos, direction, m_Damage);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->RepeatTimer(300, 15, func);
    game->PushTimer(timer);
}

Walldirection FireWallSkill::GenerateWalldirection(const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    b2Vec2 displacement = targetPos - heroPos;
    float slope = displacement.y / displacement.x;

    if (slope >= 0)
    {
        return BACKSLASH;
    }

    else 
    {
        return SLASH;
    }
}
