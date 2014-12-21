#include "stdafx.h"
#include "Lava.h"
#include "GameManager.h"
#include "Player.h"
#include "Skill.h"
#include "Lava_Damage.h"


Lava::Lava(Player* owner, b2Vec2 createPos)
{
    SetStaticBody(owner, OS_LAVA, createPos, b2Vec2(160.0f, 140.0f));
    GetBody()->SetActive(false);
    m_Pos = createPos;
    m_Owner = owner;
    m_Hp = 1000000;
    
    m_Damage = new Lava_Damage(m_Owner);
    m_Damage->LavaDamage(GetBody()->GetPosition(), REDUCE(80.0f), 10, 300);

    

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
