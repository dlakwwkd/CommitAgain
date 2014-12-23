#include "pch.h"
#include "FireEffect.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

FireEffect::FireEffect()
{
}


FireEffect::~FireEffect()
{
}

void FireEffect::CreateEffect(const Vec2& createPos)
{
    SimpleAudioEngine::getInstance()->playEffect("Music/Effect/hit.mp3");
	CreateParticle("Images/fire_explosion.plist", createPos, 0.5f, 2.0f);
}

void FireEffect::ExtinctEffect()
{
	ExtinctParticle();
}
