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
	m_MaxHp = 300;
	m_Hp = m_MaxHp;
	SetHpBar(createPos);
	m_SkillList[SKILL_Q] = new FireballSkill();
	m_SkillList[SKILL_W] = new IceballSkill();

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
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Images/MoveMotion_E.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Images/MoveMotion_W.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Images/MoveMotion_S.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Images/MoveMotion_N.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Images/MoveMotion_SE.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Images/MoveMotion_SW.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Images/MoveMotion_NE.plist");
	SpriteFrameCache::getInstance()->
		addSpriteFramesWithFile("Images/MoveMotion_NW.plist");

	//auto animation_E = Animation::create();
	//animation_E->setDelayPerUnit(0.2f);
	//auto animation_W = Animation::create();
	//animation_W->setDelayPerUnit(0.2f);
	//auto animation_S = Animation::create();
	//animation_S->setDelayPerUnit(0.2f);
	//auto animation_N = Animation::create();
	//animation_N->setDelayPerUnit(0.2f);
	//auto animation_SE = Animation::create();
	//animation_SE->setDelayPerUnit(0.2f);
	//auto animation_SW = Animation::create();
	//animation_SW->setDelayPerUnit(0.2f);
	//auto animation_NE = Animation::create();
	//animation_NE->setDelayPerUnit(0.2f);
	//auto animation_NW = Animation::create();
	//animation_NW->setDelayPerUnit(0.2f);

	//for (int i = 1; i < 8; ++i)
	//{
	//	auto frame = SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(StringUtils::format("MoveMotion_E_%02d.PNG", i));
	//	animation_E->addSpriteFrame(frame);
	//}
	//for (int i = 1; i < 8; ++i)
	//{
	//	auto frame = SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(StringUtils::format("MoveMotion_W_%02d.PNG", i));
	//	animation_W->addSpriteFrame(frame);
	//}
	//for (int i = 1; i < 8; ++i)
	//{
	//	auto frame = SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(StringUtils::format("MoveMotion_S_%02d.PNG", i));
	//	animation_S->addSpriteFrame(frame);
	//}
	//for (int i = 1; i < 8; ++i)
	//{
	//	auto frame = SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(StringUtils::format("MoveMotion_N_%02d.PNG", i));
	//	animation_N->addSpriteFrame(frame);
	//}
	//for (int i = 1; i < 8; ++i)
	//{
	//	auto frame = SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(StringUtils::format("MoveMotion_SE_%02d.PNG", i));
	//	animation_SE->addSpriteFrame(frame);
	//}
	//for (int i = 1; i < 8; ++i)
	//{
	//	auto frame = SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(StringUtils::format("MoveMotion_SW_%02d.PNG", i));
	//	animation_SW->addSpriteFrame(frame);
	//}
	//for (int i = 1; i < 8; ++i)
	//{
	//	auto frame = SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(StringUtils::format("MoveMotion_NE_%02d.PNG", i));
	//	animation_NE->addSpriteFrame(frame);
	//}
	//for (int i = 1; i < 8; ++i)
	//{
	//	auto frame = SpriteFrameCache::getInstance()->
	//		getSpriteFrameByName(StringUtils::format("MoveMotion_NW_%02d.PNG", i));
	//	animation_NW->addSpriteFrame(frame);
	//}
	/*m_MoveMotionByDir[E] = Animate::create(animation_E);
	m_MoveMotionByDir[W] = Animate::create(animation_W);
	m_MoveMotionByDir[S] = Animate::create(animation_S);
	m_MoveMotionByDir[N] = Animate::create(animation_N);
	m_MoveMotionByDir[SE] = Animate::create(animation_SE);
	m_MoveMotionByDir[SW] = Animate::create(animation_SW);
	m_MoveMotionByDir[NE] = Animate::create(animation_NE);
	m_MoveMotionByDir[NW] = Animate::create(animation_NW);*/
	/*auto animate_E = Animate::create(animation_E);
	auto animate_W = Animate::create(animation_W);
	auto animate_S = Animate::create(animation_S);
	auto animate_N = Animate::create(animation_N);
	auto animate_SE = Animate::create(animation_SE);
	auto animate_SW = Animate::create(animation_SW);
	auto animate_NE = Animate::create(animation_NE);
	auto animate_NW = Animate::create(animation_NW);*/
	/*m_MoveMotionByDir[E] = RepeatForever::create(animate_E);
	m_MoveMotionByDir[W] = RepeatForever::create(animate_W);
	m_MoveMotionByDir[S] = RepeatForever::create(animate_S);
	m_MoveMotionByDir[N] = RepeatForever::create(animate_N);
	m_MoveMotionByDir[SE] = RepeatForever::create(animate_SE);
	m_MoveMotionByDir[SW] = RepeatForever::create(animate_SW);
	m_MoveMotionByDir[NE] = RepeatForever::create(animate_NE);
	m_MoveMotionByDir[NW] = RepeatForever::create(animate_NW);*/
}
