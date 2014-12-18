#include "pch.h"
#include "HideEffect.h"


HideEffect::HideEffect()
{
}


HideEffect::~HideEffect()
{
}

void HideEffect::CreateEffect(const Vec2& createPos)
{
	CreateParticle("Images/teleport.plist", createPos, 0.4f, 2.0f);
}

void HideEffect::ExtinctEffect()
{
	ExtinctParticle();
}