#include "pch.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "SparkSkill.h"
#include "LightningSkill.h"
#include "FlashSkill.h"
#include "PacketType.h"


Jupiter::Jupiter(Vec2 createPos, float scale)
{
	m_HeroType = HERO_JUPITER;
	m_MaxHp = 1000.0f;
	m_CurHp = m_MaxHp;
	m_Speed = 450.0f;
	m_Sprite->setPosition(createPos);
	m_Sprite->setScale(scale);

	SetMoveMotionToCache();
	SetSkillMotionToCache();
	SetHpBar();

	m_RealSprite = Sprite::createWithSpriteFrameName("JupiterMove_S_01.png");
	m_RealSprite->setScale(scale);
	m_RealSprite->setAnchorPoint(Vec2(0,0));
	m_RealSprite->setPosition(-15, -10);
	m_Sprite->addChild(m_RealSprite);

    auto shadow = Sprite::create("Jupiter/Jupiter_shadow.png");
    shadow->setPosition(40, -10);
    shadow->setOpacity(150);
	m_RealSprite->addChild(shadow, -2);

	auto particle = ParticleSystemQuad::create("Jupiter/Jupiter_particle.plist");
    particle->setPosition(30, 25);
    particle->setScale(0.7f);
	m_RealSprite->addChild(particle, -1);

    m_SkillList[SKILL_Q] = new SparkSkill(this);
    m_SkillList[SKILL_W] = new LightningSkill(this);
    m_SkillList[SKILL_E] = new FlashSkill(this);
}


Jupiter::~Jupiter()
{
}

void Jupiter::SetMoveMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterMove_E.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterMove_W.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterMove_S.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterMove_N.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterMove_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterMove_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterMove_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterMove_NW.plist");
}

void Jupiter::SetMoveMotionByDir()
{
    switch (CalcMoveDirection(m_TargetPos - m_Sprite->getPosition()))
    {
    case E:  m_RealSprite->runAction(MakeAnimation("JupiterMove_E_%02d.png", 7));  break;
    case W:  m_RealSprite->runAction(MakeAnimation("JupiterMove_W_%02d.png", 7));  break;
    case S:  m_RealSprite->runAction(MakeAnimation("JupiterMove_S_%02d.png", 7));  break;
    case N:  m_RealSprite->runAction(MakeAnimation("JupiterMove_N_%02d.png", 7));  break;
    case SE: m_RealSprite->runAction(MakeAnimation("JupiterMove_SE_%02d.png", 7)); break;
    case SW: m_RealSprite->runAction(MakeAnimation("JupiterMove_SW_%02d.png", 7)); break;
    case NE: m_RealSprite->runAction(MakeAnimation("JupiterMove_NE_%02d.png", 7)); break;
    case NW: m_RealSprite->runAction(MakeAnimation("JupiterMove_NW_%02d.png", 7)); break;
    }
}

void Jupiter::SetSkillMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterQSkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterQSkill_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterQSkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterQSkill_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterWSkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterWSkill_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterWSkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterWSkill_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterESkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterESkill_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterESkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jupiter/JupiterESkill_NW.plist");
}

void Jupiter::SetSkillMotionByDir(SkillKey key)
{
    switch (key)
    {
    case SKILL_Q:
        switch (CalcSkillDirection(m_TargetPos - m_Sprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("JupiterQSkill_SE_%02d.png", 7)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("JupiterQSkill_SW_%02d.png", 7)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("JupiterQSkill_NE_%02d.png", 7)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("JupiterQSkill_NW_%02d.png", 7)); break;
        }
        break;

    case SKILL_W:
        switch (CalcSkillDirection(m_TargetPos - m_Sprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("JupiterWSkill_SE_%02d.png", 3)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("JupiterWSkill_SW_%02d.png", 3)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("JupiterWSkill_NE_%02d.png", 3)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("JupiterWSkill_NW_%02d.png", 3)); break;
        }
        break;

    case SKILL_E:
        switch (CalcSkillDirection(m_TargetPos - m_Sprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("JupiterESkill_SE_%02d.png", 2)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("JupiterESkill_SW_%02d.png", 2)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("JupiterESkill_NE_%02d.png", 2)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("JupiterESkill_NW_%02d.png", 2)); break;
        }
        break;
    }
}
