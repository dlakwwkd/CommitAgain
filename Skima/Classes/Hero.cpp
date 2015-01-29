#include "pch.h"
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



void Hero::SetSkillSprite()
{
    if (GetSkill(SKILL_Q) && GetSkill(SKILL_Q)->GetSprite())
    {
        GetSkill(SKILL_Q)->GetSprite()->setPosition(Vec2(MAX_MAP_SIZE_X / 2 - 128, 73));
        GET_UI_LAYER->addChild(GetSkill(SKILL_Q)->GetSprite());
    }
    if (GetSkill(SKILL_W) && GetSkill(SKILL_W)->GetSprite())
    {
        GetSkill(SKILL_W)->GetSprite()->setPosition(Vec2(MAX_MAP_SIZE_X / 2 - 45, 73));
        GET_UI_LAYER->addChild(GetSkill(SKILL_W)->GetSprite());
    }
    if (GetSkill(SKILL_E) && GetSkill(SKILL_E)->GetSprite())
    {
        GetSkill(SKILL_E)->GetSprite()->setPosition(Vec2(MAX_MAP_SIZE_X / 2 + 38, 72));
        GET_UI_LAYER->addChild(GetSkill(SKILL_E)->GetSprite());
    }
    if (GetSkill(SKILL_R) && GetSkill(SKILL_R)->GetSprite())
    {
        GetSkill(SKILL_R)->GetSprite()->setPosition(Vec2(MAX_MAP_SIZE_X / 2 + 119, 72));
        GET_UI_LAYER->addChild(GetSkill(SKILL_R)->GetSprite());
    }
}
