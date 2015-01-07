#include "stdafx.h"
#include "FieldType.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "Macros.h"
#include "Player.h"
#include "Timer.h"
#include "ClientSession.h"


FieldType::FieldType()
{
    m_Scale = 0.0f;
    m_CallCount = 0;
    m_TaretPos = b2Vec2(0, 0);
}


FieldType::~FieldType()
{
}

void FieldType::FieldDamage(const b2Vec2& targetPos, float scale, int damage)
{
    Rect range;
    range.m_Top = targetPos.y + scale;
    range.m_Bottom = targetPos.y - scale;
    range.m_Left = targetPos.x - scale;
    range.m_Right = targetPos.x + scale;

    GGameManager->FieldDamage(m_Owner, &range, damage);
}

b2Vec2 FieldType::GenerateNextCenterPos(Direction dir, float var)
{
    switch (dir)
    {
    case E:     return b2Vec2(m_TaretPos.x + var, m_TaretPos.y);
    case W:     return b2Vec2(m_TaretPos.x - var, m_TaretPos.y);
    case S:     return b2Vec2(m_TaretPos.x, m_TaretPos.y - var);
    case N:     return b2Vec2(m_TaretPos.x, m_TaretPos.y + var);
    case NE:    return b2Vec2(m_TaretPos.x + var, m_TaretPos.y + var);
    case SE:    return b2Vec2(m_TaretPos.x + var, m_TaretPos.y - var);
    case SW:    return b2Vec2(m_TaretPos.x - var, m_TaretPos.y - var);
    case NW:    return b2Vec2(m_TaretPos.x - var, m_TaretPos.y + var);
    }
    return m_TaretPos;
}

void FieldType::DiagonalRadiation(int repeatDelay, int repeatNum, int callNum)
{
    auto game = m_Owner->GetGame();
    auto client = m_Owner->GetClient();
    auto hero = m_Owner->GetMyHero();
    auto var = m_Scale*m_CallCount;

    auto nextAttack = [&](Direction dir)
    {
        auto nextPos = GenerateNextCenterPos(dir, var);
        Timer::Push(game, repeatDelay, repeatNum, this, &FieldType::FieldDamage, nextPos, m_Scale, m_Damage);
        client->SkillBroadCast(hero->GetUnitID(), m_TaretPos, nextPos, SKILL_R);
    };
    nextAttack(NE);
    nextAttack(SE);
    nextAttack(SW);
    nextAttack(NW);

    if (++m_CallCount == callNum)
    {
        m_CallCount = 0;
    }
}

void FieldType::CrossRadiation(int repeatDelay, int repeatNum, int callNum)
{
    auto game = m_Owner->GetGame();
    auto client = m_Owner->GetClient();
    auto hero = m_Owner->GetMyHero();
    auto var = m_Scale*m_CallCount;

    auto nextAttack = [&](Direction dir)
    {
        auto nextPos = GenerateNextCenterPos(dir, var);
        Timer::Push(game, repeatDelay, repeatNum, this, &FieldType::FieldDamage, nextPos, m_Scale, m_Damage);
        client->SkillBroadCast(hero->GetUnitID(), m_TaretPos, nextPos, SKILL_R);
    };
    nextAttack(E);
    nextAttack(W);
    nextAttack(S);
    nextAttack(N);

    if (++m_CallCount == callNum)
    {
        m_CallCount = 0;
    }
}
