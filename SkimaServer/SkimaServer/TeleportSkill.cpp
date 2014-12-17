#include "stdafx.h"
#include "TeleportSkill.h"
#include "ClientSession.h"
#include "Player.h"


TeleportSkill::TeleportSkill(Player* owner)
{
    m_Range = REDUCE(224);
    m_Owner = owner;
}


TeleportSkill::~TeleportSkill()
{
}

void TeleportSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();

    auto direction = targetPos - heroPos;
    auto distance = direction.Normalize();
	auto movePos = targetPos;

    if (distance > m_Range)
    {
        direction *= m_Range;
		movePos = heroPos + direction;
    }
	hero->GetBody()->SetTransform(movePos, 0);

    auto client = m_Owner->GetClient();
	client->SkillBroadCast(hero->GetUnitID(), heroPos, movePos, key);
}
