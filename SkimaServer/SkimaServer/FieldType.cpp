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

void FieldType::WallFieldDamage(const b2Vec2& targetPos, Walldirection direction, int damage)
{
    //switch(direction) 
    //{}
    b2Vec2 polygon[4];
    polygon[0].Set(targetPos.x, targetPos.y); // 상수연산 설정
    polygon[1].Set(targetPos.x, targetPos.y); 
    polygon[2].Set(targetPos.x, targetPos.y);
    polygon[3].Set(targetPos.x, targetPos.y);
    int32 count = 4;

    b2PolygonShape wall;
    wall.Set(polygon, count);

    
     //GGameManager->FieldDamage(m_Owner, &range, damage); // &polyfonshape 넘겨줄것


}
