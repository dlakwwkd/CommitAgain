#include "pch.h"
#include "LightningEffect.h"


LightningEffect::LightningEffect()
{
}


LightningEffect::~LightningEffect()
{
}

void LightningEffect::CreateEffect(const Vec2& createPos)
{
	CreateParticle("Images/Effect/lightning_effect.plist", createPos, 0.7f, 1.0f);
	AddSubParticle("Images/Effect/lightning.plist",		Vec2(0.5f, 0.0f), Vec2(0, 190), 0.7f);
	AddSubParticle("Images/Effect/lightning_cloud.plist", Vec2(0.0f, 0.0f), Vec2(0, 400), 0.9f);
}

void LightningEffect::ExtinctEffect()
{
	ExtinctParticle();
}