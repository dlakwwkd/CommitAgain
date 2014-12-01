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
	m_RangeShape = Sprite::create("Images/TeleportRange.png");
	m_RangeShape->addChild(hero);
}


TeleportSkill::~TeleportSkill()
{
}

void TeleportSkill::SkillReady()
{
	m_RangeShape->setVisible(true);
	//�� ��������Ʈ �ֺ����� ���׸� �׸���
}

void TeleportSkill::SkillEnd()
{
	m_RangeShape->setVisible(false);
	//setvisible(false)
}
