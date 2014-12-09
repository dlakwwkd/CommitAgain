#include "stdafx.h"
#include "TeleportSkill.h"
#include "Player.h"
#include "GameManager.h"
#include "ClientManager.h"
#include "ClientSession.h"

TeleportSkill::TeleportSkill()
{
    m_Range = 7.0f;
}

TeleportSkill::TeleportSkill(Player* owner)
{
    m_Range = 7.0f;
    m_Owner = owner;
}


TeleportSkill::~TeleportSkill()
{
}

void TeleportSkill::SkillCast(SkillType skillType, b2Vec2 heroPos, b2Vec2 targetPos)
{
    auto direction = targetPos - heroPos;
    auto distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
        
    if (distance <= m_Range) 
    {
        auto hero = m_Owner->GetMyHero();
        hero->GetBody()->SetLinearVelocity(b2Vec2{ 0, 0 });
        hero->GetBody()->SetTransform(targetPos, 0);
        hero->SetState(hero->GetStandbyState());
        auto client = GClientManager->GetClient(m_Owner->GetPlayerID());
        client->SkillBroadCast(hero->GetUnitID(), skillType, SKILL_E, heroPos, targetPos);
    }

    else //사거리보다 클때
    {
        direction.x = direction.x / distance;
        direction.y = direction.y / distance;

        b2Vec2 rangePos; 
        rangePos.x = direction.x*m_Range+heroPos.x;
        rangePos.y = direction.y*m_Range+heroPos.y;

        auto hero = m_Owner->GetMyHero();
        hero->GetBody()->SetLinearVelocity(b2Vec2{ 0, 0 });
        hero->GetBody()->SetTransform(rangePos, 0);
        hero->SetState(hero->GetStandbyState());
        auto client = GClientManager->GetClient(m_Owner->GetPlayerID());
        client->SkillBroadCast(hero->GetUnitID(), skillType, SKILL_E, heroPos, rangePos);
    }
}
