#include "pch.h"
#include "TeleportSkill.h"


TeleportSkill::TeleportSkill()
{
    m_CoolTime = 3;
    m_CanUse = true;
}
TeleportSkill::TeleportSkill(Hero* hero)
{
    m_Hero = hero;
    m_CoolTime = 5;
    m_CanUse = true;
}


TeleportSkill::~TeleportSkill()
{
}

void TeleportSkill::SkillReady()
{
    
    //�� ��������Ʈ �ֺ����� ���׸� �׸���
}

void TeleportSkill::SkillEnd()
{
    
    //setvisible(false)
}
