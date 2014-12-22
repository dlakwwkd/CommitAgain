#include "stdafx.h"
#include "HideSkill.h"
#include "ClientSession.h"
#include "Player.h"


HideSkill::HideSkill()
{
}

HideSkill::HideSkill(Player* owner)
{
    m_Owner = owner;
}


HideSkill::~HideSkill()
{
}

void HideSkill::SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos)
{
    //to do : hero�� mspeed or mHp�� �÷��ش�
    
     auto hero = m_Owner->GetMyHero();
//     hero->Crashing(false);
 
     auto client = m_Owner->GetClient();
     client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);

     //CallFuncAfter()


//      if (--repeatNum > 0)
//      {
//          CallFuncAfter(8000, this, &FieldType::FieldDamageRepeat, targetPos, scale, damage, repeatNum, repeatDelay);
//      }
}
