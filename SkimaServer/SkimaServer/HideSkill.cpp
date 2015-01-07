#include "stdafx.h"
#include "HideSkill.h"
#include "ClientSession.h"
#include "Game.h"
#include "Player.h"
#include "Laphinx.h"
#include "Timer.h"


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
    
    auto hero = m_Owner->GetMyHero();
    hero->EndMove();
    hero->EndCrash();
    hero->SetUnitHiddenState(true);
 
    auto client = m_Owner->GetClient();
    client->SkillBroadCast(hero->GetUnitID(), heroPos, targetPos, key); // Do hide

    auto mylaphinx = dynamic_cast<Laphinx*>(m_Owner->GetMyHero());

    auto game = m_Owner->GetGame();
    Timer::Push(game, 8000, mylaphinx, &Laphinx::UnHide);
}
