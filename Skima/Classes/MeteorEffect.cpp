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
    CreateParticle("Laphinx/meteorEtoW.plist", createPos, 0.7f, 0.3f);
    MeteorSequenceEffect(createPos);
}

void MeteorEffect::ExtinctEffect()
{
    ExtinctParticle();
}