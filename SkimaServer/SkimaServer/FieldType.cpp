#include "stdafx.h"
#include "FieldType.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "Macros.h"


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

void FieldType::WallFieldDamage(const b2Vec2& targetPos, WallDirection direction, int damage)
{
//     b2Vec2 polygon[4];
//     int32 count = 4;  // 기다란 직사격형 모양의 4꼭지점
//     switch (direction)
//     {
//     case SLASH:
//         polygon[0].Set(targetPos.x + Reduce(565 - 21), targetPos.y + Reduce(565 + 21)); // Up
//         polygon[1].Set(targetPos.x + Reduce(565 + 21), targetPos.y + Reduce(565 - 21)); // Right
//         polygon[2].Set(targetPos.x + Reduce(-565 + 21), targetPos.y + Reduce(-565 - 21)); // Down
//         polygon[3].Set(targetPos.x + Reduce(-565 - 21), targetPos.y + Reduce(-565 + 21)); // Left
//         break;
// 
//     case BACKSLASH:
//         polygon[0].Set(targetPos.x + Reduce(-565 + 21), targetPos.y + Reduce(565 + 21)); // Up
//         polygon[1].Set(targetPos.x + Reduce(-565 - 21), targetPos.y + Reduce(565 - 21)); // Right
//         polygon[2].Set(targetPos.x + Reduce(565 - 21), targetPos.y + Reduce(-565 - 21)); // Down
//          polygon[3].Set(targetPos.x + Reduce(565 + 21), targetPos.y + Reduce(-565 + 21)); // Left
//         break;
//     default:
//         break;
//     }
// 
//     b2PolygonShape wallShape;
//     wallShape.Set(polygon, count);
// 
//     GGameManager->WallFieldDamage(m_Owner, &wallShape, damage);
}
