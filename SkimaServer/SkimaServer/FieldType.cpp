#include "stdafx.h"
#include "FieldType.h"
#include "GameManager.h"


FieldType::FieldType()
{
    m_Scale = 0.0f;
}


FieldType::~FieldType()
{
}

void FieldType::FieldDamage(b2Vec2 targetPos, float scale, int damage)
{
    Rect range;
    range.top = targetPos.y + scale;
    range.bottom = targetPos.y - scale;
    range.left = targetPos.x - scale;
    range.right = targetPos.x + scale;

    GGameManager->FieldDamage(m_Owner, &range, damage);
}
