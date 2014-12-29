#include "pch.h"
#include "TeleportSkill.h"
#include "TeleportEffect.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

TeleportSkill::TeleportSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 3;
    m_CanUse = true;
}


TeleportSkill::~TeleportSkill()
{
}

void TeleportSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/teleport.wav");
    auto effect = new TeleportEffect();
    effect->CreateEffect(heroPos);

    m_Owner->EndMove();
    m_Owner->GetCenterSprite()->setPosition(targetPos);
}

void TeleportSkill::SkillReady()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(true);
}

void TeleportSkill::SkillEnd()
{
    auto rangeCircle = m_Owner->GetSkillRange();
    rangeCircle->setVisible(false);
}

void TeleportSkill::SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos)
{

}
