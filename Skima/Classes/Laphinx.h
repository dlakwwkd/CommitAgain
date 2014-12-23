#pragma once
#include "Hero.h"
class MeteorSkill;
class Laphinx : public Hero
{
public:
    Laphinx(Vec2 createPos, float scale);
    virtual ~Laphinx();

public:
    virtual void            SetMoveMotionByDir();
    virtual void            SetSkillMotionByDir(SkillKey key);
    ParticleSystemQuad*     GetQ_particle(){ return m_Wparticle; }

    void                    SetAllSpriteVisible();
    virtual void            HeroUnHide(Vec2 heroPos);
    MeteorSkill*            GetMeteorSKill(){ return m_MeteorSKill; }

private:
    virtual void            SetMoveMotionToCache();
    virtual void            SetSkillMotionToCache();

private:
    ParticleSystemQuad*     m_Wparticle;
    MeteorSkill*            m_MeteorSKill;

};

