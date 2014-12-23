#include "stdafx.h"
#include "FieldType.h"
#include "Scheduler.h"
#include "GameManager.h"



FieldType::FieldType()
{
    m_Scale = 0.0f;
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