#include "pch.h"
#include "BuffEffect.h"
#include "Macros.h"
#include "ObjectLayer.h"


BuffEffect::BuffEffect()
{
    m_HpFile = "Images/Effect/particle_hp_buff.plist";
}


BuffEffect::~BuffEffect()
{
}

void BuffEffect::HpEffect(const Vec2& createPos)
{
    m_Type = BUFF_HP;
    CreateParticle(m_HpFile, createPos, 0.5f, 2.0f);
}

void BuffEffect::ExtinctEffect()
{
    if (BUFF_HP)
    {
        GET_OBJECT_LAYER->removeChild(m_Particle);
    }
}
