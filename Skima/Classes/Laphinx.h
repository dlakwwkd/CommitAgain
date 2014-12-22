#pragma once
#include "Hero.h"
class Laphinx : public Hero
{
public:
    Laphinx(Vec2 createPos, float scale);
    virtual ~Laphinx();

public:
    virtual void            SetMoveMotionByDir();
    virtual void            SetSkillMotionByDir(SkillKey key);
    ParticleSystemQuad*     GetQ_particle(){ return m_Qparticle; }

    void                    SetAllSpriteVisible();
    virtual void            HeroUnHide(Vec2 heroPos);


private:
    virtual void            SetMoveMotionToCache();
    virtual void            SetSkillMotionToCache();

private:
    ParticleSystemQuad*     m_Qparticle;

};

