#include "pch.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "PacketType.h"


Jupiter::Jupiter(Vec2 createPos, float scale)
{
	//SetMoveMotionByDir();
	m_Sprite->setPosition(createPos);
	m_Sprite->setScale(scale);
	m_Sprite->addChild(m_Arrow);
	m_MaxHp = 1000.0f;
	m_CurHp = m_MaxHp;
	SetHpBar();

	switch (GET_GM.GetGameMode())
	{
	case SINGLE:
	{
		auto material = PhysicsMaterial(1.0f, 0.6f, 0.8f); // ¹Ðµµ, Åº¼º·Â, ¸¶Âû·Â

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
	m_Speed = 10.0f;
	m_HeroType = HERO_JUPITER;
}


Jupiter::~Jupiter()
{
}
