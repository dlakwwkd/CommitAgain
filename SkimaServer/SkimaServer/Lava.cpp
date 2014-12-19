#include "stdafx.h"
#include "Lava.h"
#include "GameManager.h"
#include "Player.h"


Lava::Lava(Player* owner, b2Vec2 createPos)
{
    SetStaticBody(owner, OS_LAVA, createPos, b2Vec2(240.0f, 210.0f));
    GetBody()->SetActive(false);
    m_Pos = createPos;
    m_Owner = owner;
    m_Damage = 10;

    range.m_Top = m_Pos.y + 210.0f;
    range.m_Bottom = m_Pos.y;
    range.m_Left = m_Pos.x;
    range.m_Right = m_Pos.x + 240.0f;

//         가로 240
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
