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
	CreateParticle("Laphinx/HideEffect.plist", createPos, 1.0f, 1.5f);
}

void HideEffect::ExtinctEffect()
{
	ExtinctParticle();
}