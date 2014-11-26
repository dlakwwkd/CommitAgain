#include "pch.h"
#include "Magician.h"
#include "GameManager.h"
#include "PacketType.h"
#include "FireballSkill.h"
#include "IceballSkill.h"


Magician::Magician(Point createPos, float scale)
{
	SetMoveMotionByDir();
	m_Sprite = Sprite::createWithSpriteFrameName("MoveMotion_S_03.PNG");
	m_Sprite->setPosition(createPos);
	m_Sprite->setScale(scale);
	m_Sprite->addChild(m_Arrow);
	m_MaxHp = 1000.0f;
	m_CurHp = m_MaxHp;
	SetHpBar();
	m_SkillList[SKILL_Q] = new FireballSkill(this);
	m_SkillList[SKILL_W] = new IceballSkill(this);

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
	m_Speed = 10.0f;
	m_HeroType = HERO_MAGICIAN;
}


Magician::~Magician()
{
}

void Magician::SetMoveMotionByDir()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_E.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_W.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_S.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_N.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_SE.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_SW.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_NE.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/MoveMotion_NW.plist");
}
