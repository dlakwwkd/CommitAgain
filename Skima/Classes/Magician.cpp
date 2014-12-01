#include "pch.h"
#include "Magician.h"
#include "GameManager.h"
#include "PacketType.h"
#include "FireballSkill.h"
#include "IceballSkill.h"
#include "TeleportSkill.h"


Magician::Magician(Vec2 createPos, float scale)
{
    SetMoveMotionToCache();
    m_Sprite = Sprite::createWithSpriteFrameName("MoveMotion_S_03.PNG");
    m_Sprite->setPosition(createPos);
    m_Sprite->setScale(scale);
    m_Sprite->addChild(m_Arrow);
    m_MaxHp = 1000.0f;
    m_CurHp = m_MaxHp;
    SetHpBar();
    m_TeleportRangeShape = Sprite::create("TeleportRange.PNG");
    m_SkillList[SKILL_Q] = new FireballSkill(this);
    m_SkillList[SKILL_W] = new IceballSkill(this);
    m_SkillList[SKILL_E] = new TeleportSkill(this);

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
    m_Speed = 360.0f;
}


Magician::~Magician()
{
}

void Magician::SetMoveMotionToCache()
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

void Magician::SetMoveMotionByDir()
{
    auto action = [](const char* format)
    {
        auto animation = Animation::create();
        animation->setDelayPerUnit(0.1f);

        for (int i = 1; i < 8; ++i)
        {
            auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
            animation->addSpriteFrame(frame);
        }

        return RepeatForever::create(Animate::create(animation));
    };

    auto direction = [](Vec2 displacement)
    {
        float slope = displacement.y / displacement.x;

        if (displacement.x > 0)
        {
            if (slope > -0.41f	&& slope <= 0.41f)	return Direction::E;
            if (slope > 0.41f	&& slope <= 2.41f)	return Direction::NE;
            if (slope <= -0.41f && slope > -2.41f)	return Direction::SE;
            if (slope > 2.41f)						return Direction::NE;
            if (slope <= -2.41f)						return Direction::S;
        }
        else if (displacement.x < 0)
        {
            if (slope > -0.41f	&& slope <= 0.41f)	return Direction::W;
            if (slope > 0.41f	&& slope <= 2.41f)	return Direction::SW;
            if (slope <= -0.41f && slope > -2.41f)	return Direction::NW;
            if (slope > 2.41f)						return Direction::SW;
            if (slope <= -2.41f)						return Direction::N;
        }
        else if (displacement.x == 0)
        {
            if (displacement.y < 0)					return Direction::S;
            if (displacement.y >= 0)				return Direction::N;
        }
        return Direction::E;
    };

    switch (direction(m_TargetPos - m_Sprite->getPosition()))
    {
    case E:	 m_Sprite->runAction(action("MoveMotion_E_%02d.PNG"));	break;
    case W:	 m_Sprite->runAction(action("MoveMotion_W_%02d.PNG"));	break;
    case S:	 m_Sprite->runAction(action("MoveMotion_S_%02d.PNG"));	break;
    case N:	 m_Sprite->runAction(action("MoveMotion_N_%02d.PNG"));	break;
    case SE: m_Sprite->runAction(action("MoveMotion_SE_%02d.PNG"));	break;
    case SW: m_Sprite->runAction(action("MoveMotion_SW_%02d.PNG"));	break;
    case NE: m_Sprite->runAction(action("MoveMotion_NE_%02d.PNG"));	break;
    case NW: m_Sprite->runAction(action("MoveMotion_NW_%02d.PNG"));	break;
    }
}