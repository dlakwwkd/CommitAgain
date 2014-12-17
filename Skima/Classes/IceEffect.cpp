#include "pch.h"
#include "IceEffect.h"


IceEffect::IceEffect()
{
}


IceEffect::~IceEffect()
{
}

void IceEffect::CreateEffect(const Vec2& createPos)
{
	CreateParticle("Images/ice_break.plist", createPos, 0.4f, 2.0f);
}

void IceEffect::ExtinctEffect()
{
	ExtinctParticle();
}
