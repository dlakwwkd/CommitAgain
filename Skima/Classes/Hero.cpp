﻿#include "pch.h"
#include "Hero.h"
#include "Skill.h"
#include "Buff.h"
#include "UILayer.h"


Hero::Hero()
{
    m_IsPerforming = false;
    m_UnitType = UNIT_HERO;

    m_Arrow = Sprite::create("Images/Cursor/arrow.png");
    m_Arrow->setScale(1.0f, 1.0f);
    m_Arrow->setVisible(false);
    m_CenterSprite->addChild(m_Arrow);

    m_SkillRange = Sprite::create("Images/Cursor/SkillRange.png");
    m_SkillRange->setScale(1.5f, 1.5f);
    m_SkillRange->setVisible(false);

    m_NearSkillRange = Sprite::create("Images/Cursor/nearSkillRange.png");
    m_NearSkillRange->setScale(0.5f);
    m_NearSkillRange->setOpacity(120);
    m_NearSkillRange->setVisible(false);

    m_CenterSprite->addChild(m_SkillRange);
    m_CenterSprite->addChild(m_NearSkillRange);
}


Hero::~Hero()
{
    delete m_Buff;
    m_Buff = nullptr;

    for (auto& skill : m_SkillList)
    {
        delete skill.second;
    }
}


Skill* Hero::GetSkill(SkillKey key)
{
    auto skill = m_SkillList.find(key);
    if (skill == m_SkillList.end())
    {
        return nullptr;
    }
    return skill->second;
}


int Hero::GetSkillCoolTime(SkillKey key)
{
    auto skill = GetSkill(key);
    if (!skill) return -1;

    auto cooltime = skill->GetCoolTime() - m_CooltimeBonus;
    if (cooltime < 0)
    {
        return 0;
    }
    return cooltime;
}

bool Hero::GetSkillCanUse(SkillKey key)
{
    auto skill = GetSkill(key);
    if (!skill) return false;
    return skill->GetCanUse();
}

void Hero::SetSkillCanUse(SkillKey key, bool isUse)
{
    auto skill = GetSkill(key);
    if (!skill) return;
    skill->SetCanUse(isUse);
}

void Hero::SkillCast(SkillKey key, Vec2 recvPos, Vec2 targetPos)
{
    auto skill = GetSkill(key);
    if (!skill) return;
    skill->SkillCast(recvPos, targetPos);
}

void Hero::SkillCastForEnemy(SkillKey key, Vec2 recvPos, Vec2 targetPos)
{
    auto skill = GetSkill(key);
    if (!skill) return;
    skill->SkillCastForEnemy(recvPos, targetPos);
}

void Hero::SkillReady(SkillKey key)
{
    auto skill = GetSkill(key);
    if (!skill) return;
    skill->SkillReady();
}

void Hero::SkillEnd(SkillKey key)
{
    auto skill = GetSkill(key);
    if (!skill) return;
    skill->SkillEnd();
}



RepeatForever* Hero::MakeAnimation(const char* format, int size)
{
    auto animation = Animation::create();

    if (m_HeroType == HERO_LAPHINX)
    {
        if (size < 5)
            animation->setDelayPerUnit(0.2f);
        else
            animation->setDelayPerUnit(0.05f);
    }
    else
    {
        if (size < 5)
            animation->setDelayPerUnit(0.2f);
        else
            animation->setDelayPerUnit(0.1f);
    }

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }

    return RepeatForever::create(Animate::create(animation));
}

Animate* Hero::MakeAnimationOnce(const char* format, int size)
{
    auto animation = Animation::create();

    if (m_HeroType == HERO_LAPHINX)
    {
        if (size < 5)
            animation->setDelayPerUnit(0.2f);
        else
            animation->setDelayPerUnit(0.05f);
    }
    else
    {
        if (size < 5)
            animation->setDelayPerUnit(0.2f);
        else
            animation->setDelayPerUnit(0.1f);
    }

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }

    return Animate::create(animation);
}
// Direction Hero::CalcMoveDirection(Vec2 displacement)
// {
//     float slope = displacement.y / displacement.x;
// 
//     if (displacement.x > 0)
//     {
//         if (slope > -0.41f  && slope <= 0.41f)  return Direction::E;
//         if (slope > 0.41f   && slope <= 2.41f)  return Direction::NE;
//         if (slope <= -0.41f && slope > -2.41f)  return Direction::SE;
//         if (slope > 2.41f)                      return Direction::NE;
//         if (slope <= -2.41f)                    return Direction::S;
//     }
//     else if (displacement.x < 0)
//     {
//         if (slope > -0.41f  && slope <= 0.41f)  return Direction::W;
//         if (slope > 0.41f   && slope <= 2.41f)  return Direction::SW;
//         if (slope <= -0.41f && slope > -2.41f)  return Direction::NW;
//         if (slope > 2.41f)                      return Direction::SW;
//         if (slope <= -2.41f)                    return Direction::N;
//     }
//     else if (displacement.x == 0)
//     {
//         if (displacement.y < 0)
//             return Direction::S;
//         else
//             return Direction::N;
//     }
//     return Direction::E;
// }
// 
// Direction Hero::CalcSkillDirection(Vec2 displacement)
// {
//     float slope = displacement.y / displacement.x;
// 
//     if (displacement.x > 0)
//     {
//         if (slope >= 0)
//             return Direction::NE;
//         else
//             return Direction::SE;
//     }
//     else
//     {
//         if (slope >= 0)
//             return Direction::SW;
//         else
//             return Direction::NW;
//     }
//     return Direction::SE;
// }

void Hero::SetSkillSprite()
{
    if (GetSkill(SKILL_Q) && GetSkill(SKILL_Q)->GetSprite())
    {
        GetSkill(SKILL_Q)->GetSprite()->setPosition(Vec2(442, 38));
        GET_UI_LAYER->addChild(GetSkill(SKILL_Q)->GetSprite());
    }
    if (GetSkill(SKILL_W) && GetSkill(SKILL_W)->GetSprite())
    {
        GetSkill(SKILL_W)->GetSprite()->setPosition(Vec2(518, 38));
        GET_UI_LAYER->addChild(GetSkill(SKILL_W)->GetSprite());
    }
    if (GetSkill(SKILL_E) && GetSkill(SKILL_E)->GetSprite())
    {
        GetSkill(SKILL_E)->GetSprite()->setPosition(Vec2(595, 38));
        GET_UI_LAYER->addChild(GetSkill(SKILL_E)->GetSprite());
    }
    if (GetSkill(SKILL_R) && GetSkill(SKILL_R)->GetSprite())
    {
        GetSkill(SKILL_R)->GetSprite()->setPosition(Vec2(673, 38));
        GET_UI_LAYER->addChild(GetSkill(SKILL_R)->GetSprite());
    }
}


