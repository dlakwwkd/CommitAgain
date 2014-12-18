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
	CreateParticle("Laphinx/HideEffect.plist", createPos, 0.4f, 1.0f);
}

void HideEffect::ExtinctEffect()
{
	ExtinctParticle();
}