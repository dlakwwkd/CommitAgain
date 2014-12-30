#pragma once
#include "EffectParticleType.h"
#include "PacketType.h"

class BuffEffect : public EffectParticleType
{
public:
    BuffEffect();
    virtual ~BuffEffect();

    virtual void    CreateEffect(const Vec2& createPos){}

    void            HpEffect(const Vec2& createPos);
    virtual void    ExtinctEffect();

private:
    BuffTarget      m_Type;
    char*           m_HpFile;
};

