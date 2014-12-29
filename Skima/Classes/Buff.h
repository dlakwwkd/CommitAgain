#pragma once
#include "Skill.h"

struct BuffObject
{
    BuffTarget mType;
    int        mBuffNum;
    Sprite*    mSprite;
};

typedef std::map<BuffTarget,BuffObject> BuffList;

class Buff : public Skill
{
public:
    Buff(Hero* hero);
    virtual ~Buff();
    virtual void    SkillCastForEnemy(Vec2 heroPos, Vec2 targetPos){};
    virtual void    SkillCast(Vec2 heroPos, Vec2 targetPos){};
    virtual void    SkillReady(){};
    virtual void    SkillEnd(){};

    void            BuffUse(BuffTarget type, float bonus);
    void            BuffEnd(BuffTarget type, float bonus);
    void            BuffDraw(Sprite* sprite);
    void            BuffErase(Sprite* sprite);
    

private:
    BuffList        m_BuffList;
};

