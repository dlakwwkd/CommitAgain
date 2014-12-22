#include "pch.h"
#include "ShortDashSkill.h"
#include "TeleportEffect.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"


ShortDashSkill::ShortDashSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
    m_DashCount = 2;
}

ShortDashSkill::ShortDashSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
    m_DashCount = 2;
}


ShortDashSkill::~ShortDashSkill()
{
}


void ShortDashSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    auto effect = new TeleportEffect();
    effect->CreateEffect(heroPos);

    m_Hero->EndMove();
    auto distance = heroPos.distance(targetPos);
    auto time = distance / 750.0f;
    auto action = MoveTo::create(time, targetPos);
    m_Hero->GetSprite()->runAction(action);
}

void ShortDashSkill::SkillReady()
{
    auto moveDir = m_Hero->GetArrow();
    moveDir->setVisible(true);
}

void ShortDashSkill::SkillEnd()
{
    auto moveDir = m_Hero->GetArrow();
    moveDir->setVisible(false);
}

void ShortDashSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
