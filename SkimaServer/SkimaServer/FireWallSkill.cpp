#include "stdafx.h"
#include "FireWallSkill.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"

#define MAX_CALL 4
#define REPEAT_TIME 8
#define CALL_DELAY 100
#define REPEAT_DELAY 100

FireWallSkill::FireWallSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 64;
    m_Scale = Reduce(80.0f);
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
    timer->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, func);
    game->PushTimer(timer);

    auto posFunc = std::bind(&FireWallSkill::DoNextAttack, this);
    auto posTimer = new Timer(m_Owner->GetRoomID());
    posTimer->WaitRepeatTimer(CALL_DELAY, MAX_CALL, posFunc);
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

    timerNE->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, funcNE);
    game->PushTimer(timerNE);
    timerSE->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, funcSE);
    game->PushTimer(timerSE);    
    timerSW->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, funcSW);
    game->PushTimer(timerSW);    
    timerNW->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, funcNW);
    game->PushTimer(timerNW);

    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), m_PrevTaretPos, nextPosNE, SKILL_R);
    client->SkillBroadCast(hero->GetUnitID(), m_PrevTaretPos, nextPosSE, SKILL_R);
    client->SkillBroadCast(hero->GetUnitID(), m_PrevTaretPos, nextPosSW, SKILL_R);
    client->SkillBroadCast(hero->GetUnitID(), m_PrevTaretPos, nextPosNW, SKILL_R);

    if (m_CallCount == MAX_CALL)
    {
         m_CallCount = 0;
    }
}

b2Vec2 FireWallSkill::GenerateNextCenterPos(WallDirection direction)
{
    b2Vec2 nextPos;

    switch (direction)
    {
    case N:     nextPos = b2Vec2(m_PrevTaretPos.x, m_PrevTaretPos.y + m_Scale*m_CallCount);    break;
    case S:     nextPos = b2Vec2(m_PrevTaretPos.x, m_PrevTaretPos.y + m_Scale*m_CallCount);    break;
    case W:     nextPos = b2Vec2(m_PrevTaretPos.x, m_PrevTaretPos.y + m_Scale*m_CallCount);    break;
    case E:     nextPos = b2Vec2(m_PrevTaretPos.x, m_PrevTaretPos.y + m_Scale*m_CallCount);    break;
    case NE:    nextPos = b2Vec2(m_PrevTaretPos.x + 1.414*m_Scale*m_CallCount, m_PrevTaretPos.y + 1.414*m_Scale*m_CallCount);    break;
    case SE:    nextPos = b2Vec2(m_PrevTaretPos.x + 1.414*m_Scale*m_CallCount, m_PrevTaretPos.y - 1.414*m_Scale*m_CallCount);    break;
    case SW:    nextPos = b2Vec2(m_PrevTaretPos.x - 1.414*m_Scale*m_CallCount, m_PrevTaretPos.y - 1.414*m_Scale*m_CallCount);    break;
    case NW:    nextPos = b2Vec2(m_PrevTaretPos.x - 1.414*m_Scale*m_CallCount, m_PrevTaretPos.y + 1.414*m_Scale*m_CallCount);    break;
    }
    return nextPos;
}
