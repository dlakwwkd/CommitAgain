#include "pch.h"
#include "MeteorEffect.h"


MeteorEffect::MeteorEffect()
{
}


MeteorEffect::~MeteorEffect()
{
}

void MeteorEffect::CreateEffect(const Vec2& createPos)
{
// 	CreateParticle("Jupiter/lightning_effect.plist", createPos, 0.7f, 1.0f);
// 	AddSubParticle("Jupiter/lightning.plist",		Vec2(0.5f, 0.0f), Vec2(0, 190), 0.7f);
// 	AddSubParticle("Jupiter/lightning_cloud.plist", Vec2(0.0f, 0.0f), Vec2(0, 400), 0.9f);
}

void MeteorEffect::ExtinctEffect()
{
	ExtinctParticle();
}