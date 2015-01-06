#include "stdafx.h"
#include "FireWallSkill.h"
#include "ClientSession.h"
#include "GameManager.h"
#include "Game.h"
#include "Player.h"
#include "Unit.h"
#include "Timer.h"

#define MAX_CALL 4
#define REPEAT_TIME 4
#define CALL_DELAY 50
#define REPEAT_DELAY 100

FireWallSkill::FireWallSkill(Player* owner)
{
    m_Owner = owner;
    m_Damage = 32;
    m_Scale = Reduce(80.0f);
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
    m_TaretPos = targetPos;

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto func = std::bind(&FireWallSkill::FieldDamage, this, targetPos, m_Scale, m_Damage);
    auto timer = new Timer(m_Owner->GetRoomID());
    timer->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, func);
    game->PushTimer(timer);

    auto posFunc = std::bind(&FireWallSkill::DiagonalRadiation, this);
    auto posTimer = new Timer(m_Owner->GetRoomID());
    posTimer->WaitRepeatTimer(CALL_DELAY, MAX_CALL, posFunc);
    game->PushTimer(posTimer);
}

void FireWallSkill::DiagonalRadiation()
{
    ++m_CallCount;

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto client = m_Owner->GetClient();
    auto hero = m_Owner->GetMyHero();
    auto var = m_Scale*m_CallCount;

    auto nextAttack = [&](Direction dir)
    {
        auto nextPos = GenerateNextCenterPos(dir, var);
        auto func = std::bind(&FireWallSkill::FieldDamage, this, nextPos, m_Scale, m_Damage);
        auto timer = new Timer(m_Owner->GetRoomID());
        timer->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, func);
        game->PushTimer(timer);

        client->SkillBroadCast(hero->GetUnitID(), m_TaretPos, nextPos, SKILL_R);
    };
    nextAttack(NE);
    nextAttack(SE);
    nextAttack(SW);
    nextAttack(NW);

    if (m_CallCount == MAX_CALL)
    {
         m_CallCount = 0;

         auto posFunc = std::bind(&FireWallSkill::CrossRadiation, this);
         auto posTimer = new Timer(m_Owner->GetRoomID());
         posTimer->WaitRepeatTimer(CALL_DELAY, MAX_CALL + 1, posFunc);
         game->PushTimer(posTimer);
    }
}

void FireWallSkill::CrossRadiation()
{
    ++m_CallCount;

    auto game = GGameManager->SearchGame(m_Owner->GetRoomID());
    auto client = m_Owner->GetClient();
    auto hero = m_Owner->GetMyHero();
    auto var = m_Scale*m_CallCount;

    auto nextAttack = [&](Direction dir)
    {
        auto nextPos = GenerateNextCenterPos(dir, var);
        auto func = std::bind(&FireWallSkill::FieldDamage, this, nextPos, m_Scale, m_Damage);
        auto timer = new Timer(m_Owner->GetRoomID());
        timer->RepeatTimer(REPEAT_DELAY, REPEAT_TIME, func);
        game->PushTimer(timer);

        client->SkillBroadCast(hero->GetUnitID(), m_TaretPos, nextPos, SKILL_R);
    };
    nextAttack(E);
    nextAttack(W);
    nextAttack(S);
    nextAttack(N);

    if (m_CallCount == MAX_CALL + 1)
    {
        m_CallCount = 0;
    }
}
