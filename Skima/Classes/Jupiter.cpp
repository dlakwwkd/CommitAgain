#include "pch.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "SparkSkill.h"
#include "PacketType.h"


Jupiter::Jupiter(Vec2 createPos, float scale)
{
	SetMoveMotionToCache();
	m_Sprite = Sprite::createWithSpriteFrameName("JupiterMove_S_01.png");
	m_Sprite->setPosition(createPos);
	m_Sprite->setScale(scale);
	m_Sprite->addChild(m_Arrow);
	m_MaxHp = 1000.0f;
	m_CurHp = m_MaxHp;
	SetHpBar();
	m_SkillList[SKILL_Q] = new SparkSkill(this);

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
	m_Speed = 500.0f;
}


Jupiter::~Jupiter()
{
}

void Jupiter::SetMoveMotionToCache()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/JupiterMove_E.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/JupiterMove_W.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/JupiterMove_S.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/JupiterMove_N.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/JupiterMove_SE.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/JupiterMove_SW.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/JupiterMove_NE.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/JupiterMove_NW.plist");
}

void Jupiter::SetMoveMotionByDir()
{
	switch (CalcDirection(m_TargetPos - m_Sprite->getPosition()))
	{
	case E:	 m_Sprite->runAction(MakeAnimation("JupiterMove_E_%02d.png"));	 break;
	case W:	 m_Sprite->runAction(MakeAnimation("JupiterMove_W_%02d.png"));	 break;
	case S:	 m_Sprite->runAction(MakeAnimation("JupiterMove_S_%02d.png"));	 break;
	case N:	 m_Sprite->runAction(MakeAnimation("JupiterMove_N_%02d.png"));	 break;
	case SE: m_Sprite->runAction(MakeAnimation("JupiterMove_SE_%02d.png"));  break;
	case SW: m_Sprite->runAction(MakeAnimation("JupiterMove_SW_%02d.png"));	 break;
	case NE: m_Sprite->runAction(MakeAnimation("JupiterMove_NE_%02d.png"));	 break;
	case NW: m_Sprite->runAction(MakeAnimation("JupiterMove_NW_%02d.png"));	 break;
	}
}