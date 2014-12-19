#include "pch.h"
#include "RockEffect.h"


RockEffect::RockEffect()
{
}


RockEffect::~RockEffect()
{
}

void RockEffect::CreateEffect(const Vec2& createPos)
{
    CreateParticle("Images/particle_crash_rock.plist", createPos, 0.5f, 2.0f);
}

void RockEffect::ExtinctEffect()
{
    ExtinctParticle();
}
