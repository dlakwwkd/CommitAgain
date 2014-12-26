#include "stdafx.h"
#include "MeteorSkill.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Timer.h"


MeteorSkill::MeteorSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 500;
    m_Scale = Reduce(100.0f);
}


MeteorSkill::~MeteorSkill()
{
}

void MeteorSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&MeteorSkill::FieldDamage, this, targetPos, m_Scale, m_Damage);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->CallFuncOnce(1200, func);
    game->PushTimer(timer);

    client->MeteorBroadCast(hero->GetUnitID(), targetPos);
}
