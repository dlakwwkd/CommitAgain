#include "stdafx.h"
#include "SwipeSkill.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"


SwipeSkill::SwipeSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 75;
    m_Scale = REDUCE(100);
}


SwipeSkill::~SwipeSkill()
{
}

void SwipeSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&SwipeSkill::FieldDamage, this, targetPos, m_Scale, m_Damage);
    game->RepeatTimer(300, 3, func);
}
