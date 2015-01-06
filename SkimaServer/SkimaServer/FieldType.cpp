#include "stdafx.h"
#include "FieldType.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "Macros.h"


FieldType::FieldType()
{
    m_Scale = 0.0f;
    m_CallCount = 0;
    m_TaretPos = b2Vec2(0, 0);
}


FieldType::~FieldType()
{
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

void FieldType::FieldDamage(const b2Vec2& targetPos, float scale, int damage)
{
    Rect range;
    range.m_Top = targetPos.y + scale;
    range.m_Bottom = targetPos.y - scale;
    range.m_Left = targetPos.x - scale;
    range.m_Right = targetPos.x + scale;

    GGameManager->FieldDamage(m_Owner, &range, damage);
}
