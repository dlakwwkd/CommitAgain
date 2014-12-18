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
    //to do : hero의 mspeed or mHp를 올려준다
    
    // hide start tcp 통보해주기 
    // 끝은 클라단에서 알아서 바꾸는 걸로..

     auto hero = m_Owner->GetMyHero();
//     hero->Crashing(false);
 
     auto client = m_Owner->GetClient();
     client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key);
}
