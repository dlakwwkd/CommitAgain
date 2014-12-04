#include "pch.h"
#include "Jupiter.h"
#include "GameManager.h"
#include "SparkSkill.h"
#include "LightningSkill.h"
#include "PacketType.h"


Jupiter::Jupiter(Vec2 createPos, float scale)
{
	SetMoveMotionToCache();
    SetSkillMotionToCache();
	m_Sprite = Sprite::createWithSpriteFrameName("JupiterMove_S_01.png");
	auto shadow = Sprite::create("Images/Jupiter_shadow.png");
	shadow->setPosition(Vec2(45.0f, -25.0f));
	m_Sprite->addChild(shadow);
	m_Sprite->setPosition(createPos);
	m_Sprite->setScale(scale);
	m_Sprite->addChild(m_Arrow);
    m_Sprite->addChild(m_SkillRange);
	m_MaxHp = 1000.0f;
	m_CurHp = m_MaxHp;
	SetHpBar();
    m_SkillList[SKILL_Q] = new SparkSkill(this);
    m_SkillList[SKILL_W] = new LightningSkill(this);

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
    case E:  m_Sprite->runAction(MakeAnimation("JupiterMove_E_%02d.png", 7));  break;
    case W:  m_Sprite->runAction(MakeAnimation("JupiterMove_W_%02d.png", 7));  break;
    case S:  m_Sprite->runAction(MakeAnimation("JupiterMove_S_%02d.png", 7));  break;
    case N:  m_Sprite->runAction(MakeAnimation("JupiterMove_N_%02d.png", 7));  break;
    case SE: m_Sprite->runAction(MakeAnimation("JupiterMove_SE_%02d.png", 7)); break;
    case SW: m_Sprite->runAction(MakeAnimation("JupiterMove_SW_%02d.png", 7)); break;
    case NE: m_Sprite->runAction(MakeAnimation("JupiterMove_NE_%02d.png", 7)); break;
    case NW: m_Sprite->runAction(MakeAnimation("JupiterMove_NW_%02d.png", 7)); break;
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
}

void Jupiter::SetSkillMotionByDir(SkillKey key)
{
    switch (key)
    {
    case SKILL_Q:
        switch (CalcSkillDirection(m_TargetPos - m_Sprite->getPosition()))
        {
        case SE: m_Sprite->runAction(MakeAnimation("JupiterQSkill_SE_%02d.png", 7)); break;
        case SW: m_Sprite->runAction(MakeAnimation("JupiterQSkill_SW_%02d.png", 7)); break;
        case NE: m_Sprite->runAction(MakeAnimation("JupiterQSkill_NE_%02d.png", 7)); break;
        case NW: m_Sprite->runAction(MakeAnimation("JupiterQSkill_NW_%02d.png", 7)); break;
        }
        break;

    case SKILL_W:
        switch (CalcSkillDirection(m_TargetPos - m_Sprite->getPosition()))
        {
        case SE: m_Sprite->runAction(MakeAnimation("JupiterWSkill_SE_%02d.png", 3)); break;
        case SW: m_Sprite->runAction(MakeAnimation("JupiterWSkill_SW_%02d.png", 3)); break;
        case NE: m_Sprite->runAction(MakeAnimation("JupiterWSkill_NE_%02d.png", 3)); break;
        case NW: m_Sprite->runAction(MakeAnimation("JupiterWSkill_NW_%02d.png", 3)); break;
        }
        break;
    }
}
