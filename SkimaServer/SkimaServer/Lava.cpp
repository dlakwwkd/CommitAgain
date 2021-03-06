#include "stdafx.h"
#include "Lava.h"
#include "GameManager.h"
#include "Player.h"
#include "Skill.h"
#include "LavaDamageSkill.h"


Lava::Lava(Player* owner, b2Vec2 createPos)
{
    SetStaticBody(owner, OS_LAVA, createPos, b2Vec2(160.0f, 140.0f));
    GetBody()->SetActive(false);
    m_Pos = createPos;
    m_Owner = owner;
    m_Hp = 10000;
    
    m_Damage = new LavaDamageSkill(m_Owner);
    m_Damage->LavaDamage(GetBody()->GetPosition(), Reduce(80.0f), 10, 300);
}


Lava::~Lava()
{
    delete m_Damage;
}
