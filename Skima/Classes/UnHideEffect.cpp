#include "pch.h"
#include "UnHideEffect.h"


UnHideEffect::UnHideEffect()
{
}


UnHideEffect::~UnHideEffect()
{
}

void UnHideEffect::CreateEffect(const Vec2& createPos)
{
    CreateSprite("Laphinx/ExclamationMark.png", createPos, 0.3f, 1.0f);
}

void UnHideEffect::ExtinctEffect()
{
    ExtinctSprite();
}