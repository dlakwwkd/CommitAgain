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

 //   auto direction = GenerateWalldirection(heroPos, targetPos);

//     auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
// //    auto func = std::bind(&FireWallSkill::WallFieldDamage, this, targetPos, direction, m_Damage * hero->GetDamageBonus());
//     auto timer = new Timer(m_Owner->GetRoomID());
//     timer->RepeatTimer(300, 15, func);
//     game->PushTimer(timer);
}


// void FireWallSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
// {
//     auto hero = m_Owner->GetMyHero();
//     hero->EndMove();
// 
//     auto client = m_Owner->GetClient();
//     client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);
// 
//     auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
//     auto func = std::bind(&FireWallSkill::FieldDamage, this, targetPos, m_Scale, m_Damage*hero->GetDamageBonus());
//     auto timer = new Timer(m_Owner->GetRoomID());
//     timer->RepeatTimer(300, 10, func);
//     game->PushTimer(timer);
// 
// 
// 
// 
//     auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
//     auto func = std::bind(&SwipeSkill::FieldDamage, this, attackPos, Reduce(80.0f), m_Damage*hero->GetDamageBonus());
//     auto timer = new Timer(m_Owner->GetRoomID());
//     timer->RepeatTimer(300, 3, func);
//     game->PushTimer(timer);
// }


void FireWallSkill::DoNextAttack(int attackCount)
{

}

b2Vec2 FireWallSkill::GenerateNextCenterPos(WallDirection direction, float radius, b2Vec2 curPos)
{
    b2Vec2 nextPos;

    switch (direction)
    {
    case NE:
        nextPos = b2Vec2(curPos.x + 1.414*radius, curPos.y + 1.414*radius);
        break;
    case SE:
        nextPos = b2Vec2(curPos.x + 1.414*radius, curPos.y - 1.414*radius);
        break;
    case SW:
        nextPos = b2Vec2(curPos.x - 1.414*radius, curPos.y - 1.414*radius);
        break;
    case NW:
        nextPos = b2Vec2(curPos.x - 1.414*radius, curPos.y + 1.414*radius);
        break;
    }
    return nextPos;
}
