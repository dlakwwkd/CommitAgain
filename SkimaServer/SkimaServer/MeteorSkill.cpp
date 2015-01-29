#include "stdafx.h"
#include "MeteorSkill.h"
#include "ClientSession.h"
#include "Game.h"
#include "Player.h"
#include "Timer.h"


MeteorSkill::MeteorSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 500;
    m_Scale = Reduce(130.0f);
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

    auto game = m_Owner->GetGame();
    Timer::Push(game, 1200, this, &MeteorSkill::FieldDamage, targetPos, m_Scale, m_Damage);

    client->EffectBroadCast(EF_METEOR, targetPos);
}
