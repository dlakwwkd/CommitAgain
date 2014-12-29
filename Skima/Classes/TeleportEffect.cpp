#include "pch.h"
#include "TeleportEffect.h"


TeleportEffect::TeleportEffect()
{
}


TeleportEffect::~TeleportEffect()
{
}

void TeleportEffect::CreateEffect(const Vec2& createPos)
{
	CreateParticle("Images/Effect/teleport.plist", createPos, 0.4f, 2.0f);
}

void TeleportEffect::ExtinctEffect()
{
	ExtinctParticle();
}