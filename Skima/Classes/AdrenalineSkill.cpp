#include "pch.h"
#include "AdrenalineSkill.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"


AdrenalineSkill::AdrenalineSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
}

AdrenalineSkill::AdrenalineSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}


AdrenalineSkill::~AdrenalineSkill()
{
}


void AdrenalineSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    // m_hero의 Qparticle을 setvisible해준다


//     auto effect = new TeleportEffect();
//     effect->CreateEffect(heroPos);
// 
//     m_Hero->EndMove();
//     auto distance = heroPos.distance(targetPos);
//     auto time = distance / 1500.0f;
//     auto action = MoveTo::create(time, targetPos);
//     m_Hero->GetSprite()->runAction(action);
}

void AdrenalineSkill::SkillReady()
{
//     auto moveDir = m_Hero->GetArrow();
//     moveDir->setVisible(true);
}

void AdrenalineSkill::SkillEnd()
{
//     auto moveDir = m_Hero->GetArrow();
//     moveDir->setVisible(false);
}