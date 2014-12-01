#pragma once
#include "Hero.h"
class Magician : public Hero
{
public:
    Magician(Vec2 createPos, float scale);
    virtual ~Magician();

public:
    void			    SetMoveMotionToCache();
    virtual void	    SetMoveMotionByDir();
    ParticleSystemQuad* GetTeleportParticle(){ return m_TeleportParticle; }

private:
    Sprite*             m_TeleportRangeShape;
    ParticleSystemQuad* m_TeleportParticle;
};

