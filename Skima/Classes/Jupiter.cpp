#include "pch.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "SparkSkill.h"
#include "LightningSkill.h"
#include "FlashSkill.h"
#include "PacketType.h"
#include "Buff.h"



Jupiter::Jupiter(Vec2 createPos, float scale)
{
	m_HeroType = HERO_JUPITER;
	m_MaxHp = 1200.0f;
	m_CurHp = m_MaxHp;
	m_Speed = 370.0f;
	m_CenterSprite->setPosition(createPos);
	m_CenterSprite->setScale(scale);

	SetMoveMotionToCache();
	SetSkillMotionToCache();

	m_RealSprite = Sprite::createWithSpriteFrameName("JupiterMove_S_01.png");
    m_RealSprite->setScale(scale);
    m_RealSprite->setPosition(Vec2(0, 20));
	m_CenterSprite->addChild(m_RealSprite);

    auto shadow = Sprite::create("Images/Unit/unit_shadow.png");
    shadow->setPosition(40, -10);
    shadow->setOpacity(150);
	m_RealSprite->addChild(shadow, -2);

	auto particle = ParticleSystemQuad::create("Images/Unit/Jupiter/Jupiter_particle.plist");
    particle->setPosition(30, 25);
    particle->setScale(0.7f);
	m_RealSprite->addChild(particle, -1);

    m_SkillList[SKILL_Q] = new SparkSkill(this);
    m_SkillList[SKILL_W] = new LightningSkill(this);
    m_SkillList[SKILL_E] = new FlashSkill(this);

    m_Buff = new Buff(this);
}


Jupiter::~Jupiter()
{
}

void Jupiter::SetMoveMotionToCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterMove_E.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterMove_W.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterMove_S.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterMove_N.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterMove_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterMove_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterMove_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterMove_NW.plist");
}

void Jupiter::SetMoveMotionByDir()
{
    switch (CalcMoveDirection(m_TargetPos - m_CenterSprite->getPosition()))
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
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterQSkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterQSkill_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterQSkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterQSkill_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterWSkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterWSkill_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterWSkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterWSkill_NW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterESkill_SE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterESkill_SW.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterESkill_NE.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Unit/Jupiter/JupiterESkill_NW.plist");
}

void Jupiter::SetSkillMotionByDir(SkillKey key)
{
    switch (key)
    {
    case SKILL_Q:
        switch (CalcSkillDirection(m_TargetPos - m_CenterSprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("JupiterQSkill_SE_%02d.png", 7)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("JupiterQSkill_SW_%02d.png", 7)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("JupiterQSkill_NE_%02d.png", 7)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("JupiterQSkill_NW_%02d.png", 7)); break;
        }
        break;

    case SKILL_W:
        switch (CalcSkillDirection(m_TargetPos - m_CenterSprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("JupiterWSkill_SE_%02d.png", 3)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("JupiterWSkill_SW_%02d.png", 3)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("JupiterWSkill_NE_%02d.png", 3)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("JupiterWSkill_NW_%02d.png", 3)); break;
        }
        break;

    case SKILL_E:
        switch (CalcSkillDirection(m_TargetPos - m_CenterSprite->getPosition()))
        {
        case SE: m_RealSprite->runAction(MakeAnimationOnce("JupiterESkill_SE_%02d.png", 2)); break;
        case SW: m_RealSprite->runAction(MakeAnimationOnce("JupiterESkill_SW_%02d.png", 2)); break;
        case NE: m_RealSprite->runAction(MakeAnimationOnce("JupiterESkill_NE_%02d.png", 2)); break;
        case NW: m_RealSprite->runAction(MakeAnimationOnce("JupiterESkill_NW_%02d.png", 2)); break;
        }
        break;
    }
}

void Jupiter::HeroUnHide(Vec2 heroPos)
{

}
