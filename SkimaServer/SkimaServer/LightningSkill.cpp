#include "stdafx.h"
#include "LightningSkill.h"
#include "ClientSession.h"
#include "Player.h"
#include "GameManager.h"
#include "Game.h"
#include "Timer.h"


LightningSkill::LightningSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 75;
    m_Scale = Reduce(100.0f);
}


LightningSkill::~LightningSkill()
{
}

void LightningSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&LightningSkill::FieldDamage, this, targetPos, m_Scale, m_Damage);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->RepeatTimer(200, 5, func);
    game->PushTimer(timer);
}
