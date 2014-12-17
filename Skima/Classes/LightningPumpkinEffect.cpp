#include "pch.h"
#include "LightningPumpkinEffect.h"


LightningPumpkinEffect::LightningPumpkinEffect()
{
}


LightningPumpkinEffect::~LightningPumpkinEffect()
{
}

void LightningPumpkinEffect::CreateEffect(const Vec2& createPos)
{
	CreateParticle("Jupiter/LightningPumpkin.plist", createPos, 0.4f, 2.0f);
}

void LightningPumpkinEffect::ExtinctEffect()
{
	ExtinctParticle();
}
