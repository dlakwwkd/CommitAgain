#include "pch.h"
#include "HideSkill.h"
#include "GameManager.h"
#include "Hero.h"
#include "Unit.h"
#include "HideEffect.h"
#include "ObjectLayer.h"
#include "UnHideEffect.h"
#include "Laphinx.h"
#include "ObjectLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

HideSkill::HideSkill(Hero* hero)
{
    m_Owner = hero;
    m_CoolTime = 9;
    m_HiddenTime = 5;
    m_CanUse = true;
    CreateSprite("Images/Interface/hide.jpg");
}


HideSkill::~HideSkill()
{
}


void HideSkill::SkillCast(Vec2 heroPos, Vec2 targetPos)
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/hide.mp3");
    auto effect = new HideEffect();
    effect->CreateEffect(heroPos);
}

void HideSkill::SkillReady()
{

}

void HideSkill::SkillEnd()
{

}