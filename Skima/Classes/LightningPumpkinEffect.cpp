#include "pch.h"
#include "LightningPumpkinEffect.h"


LightningPumpkinEffect::LightningPumpkinEffect(const Vec2& targetPos)
{
    m_Sprite->setOpacity(160);
    SetPumpkinCache();
//     m_MeteorParticle = ParticleSystemQuad::create("Images/Effect/meteorEtoW.plist");
// 
//     auto initPos = GenerateInitPos(targetPos);
//     m_MeteorParticle->setPosition(initPos);
//     m_MeteorParticle->setScale(1.0f);
//     m_MeteorParticle->setVisible(false);
//     GET_OBJECT_LAYER->addChild(m_MeteorParticle, 20);

//     auto action1 = DelayTime::create(1.0f);
//     auto action2 = CallFunc::create(CC_CALLBACK_0(LightningPumpkinEffect::SetParticleVisible, this, m_MeteorParticle));
//     auto action3 = MoveTo::create(0.2f, targetPos);
//     auto action4 = CallFunc::create(CC_CALLBACK_0(LightningPumpkinEffect::ExtinctMeteorParticle, this));
//     auto action5 = CallFunc::create(CC_CALLBACK_0(LightningPumpkinEffect::ShowExplodeSprite, this));
//     auto action6 = Sequence::create(action1, action2, action3, action4, action5, NULL);
    //m_MeteorParticle->runAction(action6);
}

LightningPumpkinEffect::~LightningPumpkinEffect()
{
}

void LightningPumpkinEffect::CreateEffect(const Vec2& createPos)
{
    CreateSprite("Images/Unit/CloackingUnit.png", createPos, 1.5f, 3.0f);
    ShowPumpkinSprite();
}

void LightningPumpkinEffect::ExtinctEffect()
{
    ExtinctSprite();
}

// void LightningPumpkinEffect::ExtinctMeteorParticle()
// {
//    /* GET_OBJECT_LAYER->removeChild(m_MeteorParticle);*/
// }

void LightningPumpkinEffect::SetPumpkinCache()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Effect/LightningPumpkin.plist");
}

void LightningPumpkinEffect::ShowPumpkinSprite()
{
    m_Sprite->runAction(MakeAnimationForever("LightningPumpkin_%02d.PNG", 6));
}

void LightningPumpkinEffect::SetParticleVisible(ParticleSystemQuad* particle)
{
    particle->setVisible(true);
}
	
