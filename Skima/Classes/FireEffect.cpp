#include "pch.h"
#include "FireEffect.h"

FireEffect::FireEffect()
{
}


FireEffect::~FireEffect()
{
}

void FireEffect::CreateEffect(const Vec2& createPos)
{
	CreateParticle("Images/Effect/fire_explosion.plist", createPos, 0.5f, 2.0f);
}

void FireEffect::ExtinctEffect()
{
	ExtinctParticle();
}
