#include "pch.h"
#include "FireWallEffect.h"
#include "ObjectLayer.h"

FireWallEffect::FireWallEffect()
{
    m_FireSprite1 = Sprite::create("Images/Unit/CloackingUnit.png");
    m_FireSprite2 = Sprite::create("Images/Unit/CloackingUnit.png");
    m_FireSprite3 = Sprite::create("Images/Unit/CloackingUnit.png");
    m_FireSprite4 = Sprite::create("Images/Unit/CloackingUnit.png");
    m_FireSprite5 = Sprite::create("Images/Unit/CloackingUnit.png");
    m_FireSprite6 = Sprite::create("Images/Unit/CloackingUnit.png");
    m_FireSprite7 = Sprite::create("Images/Unit/CloackingUnit.png");
    m_FireSprite8 = Sprite::create("Images/Unit/CloackingUnit.png");

    m_FireParticle = ParticleSystemQuad::create("Images/Effect/FireWall/FireWallParticle.plist");
    m_FireParticle->setScale(1.0f);
    m_FireParticle->setVisible(false);
}

FireWallEffect::~FireWallEffect()
{
}

void FireWallEffect::CreateEffect(const Vec2& createPos)
{
}

void FireWallEffect::CreateFireEffect(Vec2 createPos)
{
    float scale = 1.0f;
    CreateFireSubSprite(m_FireSprite1,Vec2(createPos.x - scale*15, createPos.y + scale*12), scale, 4.5f);
    CreateFireSubSprite(m_FireSprite2,Vec2(createPos.x + scale*17, createPos.y + scale*18), scale, 4.5f);
    CreateFireSubSprite(m_FireSprite3,Vec2(createPos.x + scale*20, createPos.y + scale*15), scale, 4.5f);
    CreateFireSubSprite(m_FireSprite4,Vec2(createPos.x + scale*25, createPos.y - scale*20), scale, 4.5f);
    CreateFireSubSprite(m_FireSprite5,Vec2(createPos.x + scale*15, createPos.y - scale*18), scale, 4.5f);
    CreateFireSubSprite(m_FireSprite6,Vec2(createPos.x - scale*0, createPos.y - scale*12), scale, 4.5f);
    CreateFireSubSprite(m_FireSprite7,Vec2(createPos.x - scale*20, createPos.y - scale*11), scale, 4.5f);
    CreateFireSubSprite(m_FireSprite8,Vec2(createPos.x - scale*18, createPos.y + scale*16), scale, 4.5f);
    CreateSprite("Images/Unit/CloackingUnit.png", createPos, scale, 4.5f);
    SetFireMotionCache();
    ShowFireMotion();

    m_FireParticle->setPosition(Vec2(createPos.x,createPos.y-scale*40));
    m_FireParticle->setVisible(true);
    GET_OBJECT_LAYER->addChild(m_FireParticle);
}

void FireWallEffect::ExtinctEffect()
{
    ExtinctSprite();
}

void FireWallEffect::SetFireMotionCache()
{
     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Effect/FireWall/fire.plist");
     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Effect/FireWall/fireA.plist");
     SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Images/Effect/FireWall/fireB.plist");
}

void FireWallEffect::ShowFireMotion()
{
     m_FireSprite1->runAction(MakeFastAnimationForever("fire_A%02d.png", 25));
     m_FireSprite2->runAction(MakeFastAnimationForever("fire_B%02d.png", 25));
     m_FireSprite3->runAction(MakeFastAnimationForever("fire%02d.png", 25));
     m_FireSprite4->runAction(MakeFastAnimationForever("fire_A%02d.png", 25));
     m_FireSprite5->runAction(MakeFastAnimationForever("fire_B%02d.png", 25));
     m_FireSprite6->runAction(MakeFastAnimationForever("fire%02d.png", 25));
     m_FireSprite7->runAction(MakeFastAnimationForever("fire_A%02d.png", 25));
     m_FireSprite8->runAction(MakeFastAnimationForever("fire_B%02d.png", 25));
     m_Sprite->runAction(MakeFastAnimationForever("fire%02d.png", 25));

}
