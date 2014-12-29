#include "pch.h"
#include "EffectSpriteType.h"
#include "ObjectLayer.h"
#include "Macros.h"


EffectSpriteType::EffectSpriteType()
{
}


EffectSpriteType::~EffectSpriteType()
{
}

void EffectSpriteType::CreateSprite(const char* file, const Vec2& createPos, float scale, float lastTime)
{
    m_Sprite = Sprite::create(file);
    m_Sprite->setPosition(createPos);
    m_Sprite->setScale(scale);
    auto action1 = DelayTime::create(lastTime);
    auto action2 = CallFunc::create(CC_CALLBACK_0(EffectSpriteType::ExtinctSprite, this));
    auto action3 = Sequence::create(action1, action2, NULL);
    m_Sprite->runAction(action3);
    GET_OBJECT_LAYER->addChild(m_Sprite, 20);
}

void EffectSpriteType::AddSubSprite(const char* file, const Vec2& anchorPoint, const Vec2& createPos, float scale)
{
    auto sprite = Sprite::create(file);
    sprite->setAnchorPoint(anchorPoint);
    sprite->setPosition(createPos);
    sprite->setScale(scale);
    m_Sprite->addChild(sprite);
}

Animate* EffectSpriteType::MakeAnimationOnce(const char* format, int size)
{
    auto animation = Animation::create();

    if (size < 5)       animation->setDelayPerUnit(0.2f);
    else if (size >= 5) animation->setDelayPerUnit(0.1f);

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }

    return Animate::create(animation);
}

void EffectSpriteType::ExtinctSprite()
{
    GET_OBJECT_LAYER->removeChild(m_Sprite);
    delete this;
}

Animate* EffectSpriteType::MakeFastAnimationOnce(const char* format, int size)
{
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.05f);
    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }
    return Animate::create(animation);
}

RepeatForever* EffectSpriteType::MakeFastAnimationForever(const char* format, int size)
{
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.05f);

    for (int i = 1; i < size + 1; ++i)
    {
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(format, i));
        animation->addSpriteFrame(frame);
    }

    return RepeatForever::create(Animate::create(animation));
}