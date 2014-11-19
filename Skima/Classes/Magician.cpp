#include "pch.h"
#include "Magician.h"
#include "GameManager.h"
#include "PacketType.h"
#include "FireballSkill.h"


Magician::Magician(Point createPos, float scale)
{
	m_Sprite = Sprite::create("Images/Magician.png");
	m_Sprite->setPosition(createPos);
	m_Sprite->setScale(scale);
	m_SkillList[SKILL_Q] = new FireballSkill();

	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
	{
		auto material = PhysicsMaterial(1.0f, 0.6f, 0.8f); // 밀도, 탄성력, 마찰력

		m_Body = PhysicsBody::createCircle(m_Sprite->getContentSize().width*(scale / 2), material);
		m_Body->setMass(1.0f);
		m_Body->setLinearDamping(3);
		m_Body->setRotationEnable(false);

		m_Sprite->setPhysicsBody(m_Body);
		break;
	}
	case MULTI:
		break;
	}

	m_MaxHp = 300;
	m_Hp = m_MaxHp;
	m_HeroType = HERO_MAGICIAN;
}


Magician::~Magician()
{
}
