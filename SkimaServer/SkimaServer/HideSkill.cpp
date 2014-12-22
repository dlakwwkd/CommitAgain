#include "stdafx.h"
#include "HideSkill.h"
#include "ClientSession.h"
#include "Player.h"
#include "Laphinx.h"
#include "Scheduler.h"

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

     //CallFuncAfter() -> laphinx���� 
     //CallFuncAfter(8000, m_Owner->GetMyHero(), &Laphinx::UnHide);
      
}
