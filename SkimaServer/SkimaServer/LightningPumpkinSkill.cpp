#include "stdafx.h"
#include "LightningPumpkinSkill.h"
#include "ClientSession.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"
#include <time.h>


LightningPumpkinSkill::LightningPumpkinSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 64;
    m_Scale = Reduce(80.0f);
}


LightningPumpkinSkill::~LightningPumpkinSkill()
{
}

void LightningPumpkinSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    m_TaretPos = targetPos;

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

    auto game = m_Owner->GetGame();
    Timer::Push(game, 200, 10, this, &LightningPumpkinSkill::RandomAttack, Reduce(200.0f), 200, 5, 10, EF_LIGHTNING);
}
