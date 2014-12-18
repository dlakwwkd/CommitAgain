#include "pch.h"
#include "HideSkill.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"


HideSkill::HideSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
}

HideSkill::HideSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}


HideSkill::~HideSkill()
{
}


void HideSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    // m_hero�� Qparticle�� setvisible���ش�
    // m_hero �� ������ setopacity 2�ܰ�
    // ������ �ƴϸ� setopacity 2~3�ܰ� + getrealsprite -> setvisible(f)

//     auto effect = new TeleportEffect();
//     effect->CreateEffect(heroPos);
// 
//     m_Hero->EndMove();
//     auto distance = heroPos.distance(targetPos);
//     auto time = distance / 1500.0f;
//     auto action = MoveTo::create(time, targetPos);
//     m_Hero->GetSprite()->runAction(action);
}
void HideSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{
    //���������� �� �����ǿ� ��ƼŬ ����ֱ�
}

void HideSkill::SkillReady()
{
//     auto moveDir = m_Hero->GetArrow();
//     moveDir->setVisible(true);
}

void HideSkill::SkillEnd()
{
//     auto moveDir = m_Hero->GetArrow();
//     moveDir->setVisible(false);
}

