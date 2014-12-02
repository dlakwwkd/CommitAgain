#include "pch.h"
#include "Effect.h"


Effect::Effect()
{
    m_EffectType = EF_NONE;
    m_Sprite = nullptr;
    m_InUse = false;
    m_ID = -1;
}


Effect::~Effect()
{
}
