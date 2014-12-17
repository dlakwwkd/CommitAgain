#include "stdafx.h"
#include "Lava.h"
#include "GameManager.h"


Lava::Lava(b2Vec2 createPos)
{
    m_Pos = createPos;

    Rect range;
    range.top = m_Pos.y;
    range.bottom = m_Pos.y + 210.0f;
    range.left = m_Pos.x;
    range.right = m_Pos.x + 240.0f;

//     가로 240
//         세로 210
// 
//         7 * 5
// 
//         1680 = 2 5 3 7 8
//         1050 = 2 5 3 5 7

    //GGameManager->FieldDamage(m_Owner, &range, damage);
}


Lava::~Lava()
{
}
