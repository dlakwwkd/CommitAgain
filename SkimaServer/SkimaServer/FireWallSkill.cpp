#include "stdafx.h"
#include "FireWallSkill.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"

#define MAXCALL 3
#define REPEATTIME 5

FireWallSkill::FireWallSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 75;
    m_Scale = Reduce(100.0f);
    m_CallCount = 0;
    m_PrevTaretPos = b2Vec2(-1, -1);
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
    m_PrevTaretPos = targetPos;

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&FireWallSkill::FieldDamage, this, targetPos, m_Scale, m_Damage);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->RepeatTimer(300, REPEATTIME, func);
    game->PushTimer(timer);

    auto posTimer = new Timer(m_Owner->GetRoomID());

    auto posFunc = std::bind(&FireWallSkill::DoNextAttack, this);
    posTimer->WaitRepeatTimer(300, MAXCALL, posFunc);
    game->PushTimer(posTimer);
}

void FireWallSkill::DoNextAttack()
{
    m_CallCount++;
    auto hero = m_Owner->GetMyHero();
    
    auto nextPosNE = GenerateNextCenterPos(NE);
    auto nextPosSE = GenerateNextCenterPos(SE);
    auto nextPosNW = GenerateNextCenterPos(NW);
    auto nextPosSW = GenerateNextCenterPos(SW);

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto funcNE = std::bind(&FireWallSkill::FieldDamage, this, nextPosNE, m_Scale, m_Damage);
    auto funcSE = std::bind(&FireWallSkill::FieldDamage, this, nextPosSE, m_Scale, m_Damage);
    auto funcNW = std::bind(&FireWallSkill::FieldDamage, this, nextPosNW, m_Scale, m_Damage);
    auto funcSW = std::bind(&FireWallSkill::FieldDamage, this, nextPosSW, m_Scale, m_Damage);
    auto timerNE = new Timer(m_Owner->GetRoomID());
    auto timerSE = new Timer(m_Owner->GetRoomID());
    auto timerSW = new Timer(m_Owner->GetRoomID());
    auto timerNW = new Timer(m_Owner->GetRoomID());

    timerNE->RepeatTimer(300, REPEATTIME, funcNE);
    game->PushTimer(timerNE);
    timerSE->RepeatTimer(300, REPEATTIME, funcSE);
    game->PushTimer(timerSE);    
    timerSW->RepeatTimer(300, REPEATTIME, funcSW);
    game->PushTimer(timerSW);    
    timerNW->RepeatTimer(300, REPEATTIME, funcNW);
    game->PushTimer(timerNW);

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), m_PrevTaretPos, nextPosNE, SKILL_R);
    client->SkillBroadCast(hero->GetUnitID(), m_PrevTaretPos, nextPosSE, SKILL_R);
    client->SkillBroadCast(hero->GetUnitID(), m_PrevTaretPos, nextPosSW, SKILL_R);
    client->SkillBroadCast(hero->GetUnitID(), m_PrevTaretPos, nextPosNW, SKILL_R);

    if (m_CallCount == MAXCALL)
    {
         m_CallCount = 0;
    }
}

b2Vec2 FireWallSkill::GenerateNextCenterPos(WallDirection direction)
{
    b2Vec2 nextPos;

    switch (direction)
    {
    case NE:
        nextPos = b2Vec2(m_PrevTaretPos.x + 1.414*m_Scale*m_CallCount, m_PrevTaretPos.y + 1.414*m_Scale*m_CallCount);
        break;
    case SE:
        nextPos = b2Vec2(m_PrevTaretPos.x + 1.414*m_Scale*m_CallCount, m_PrevTaretPos.y - 1.414*m_Scale*m_CallCount);
        break;
    case SW:
        nextPos = b2Vec2(m_PrevTaretPos.x - 1.414*m_Scale*m_CallCount, m_PrevTaretPos.y - 1.414*m_Scale*m_CallCount);
        break;
    case NW:
        nextPos = b2Vec2(m_PrevTaretPos.x - 1.414*m_Scale*m_CallCount, m_PrevTaretPos.y + 1.414*m_Scale*m_CallCount);
        break;
    }
    return nextPos;
}
