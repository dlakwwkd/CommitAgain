#include "pch.h"
#include "FireWallParticleEffect.h"

FireWallParticleEffect::FireWallParticleEffect()
{
}


FireWallParticleEffect::~FireWallParticleEffect()
{
}

void FireWallParticleEffect::CreateEffect(const Vec2& createPos)
{
	CreateParticle("Images/Effect/FireWallParticle.plist", createPos, 0.85f, 2.9f);
}

void FireWallParticleEffect::ExtinctEffect()
{
	ExtinctParticle();
}
