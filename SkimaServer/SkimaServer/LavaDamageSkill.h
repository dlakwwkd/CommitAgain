#pragma once
#include "FieldType.h"
class Timer;

class LavaDamageSkill : public FieldType
{
public:
    LavaDamageSkill(Player* owner);
    virtual ~LavaDamageSkill();

    virtual void SkillCast(SkillKey key, const b2Vec2& heroPos, const b2Vec2& targetPos){}
    virtual void CastStop(){}

    void LavaDamage(b2Vec2 createPos, float scale, int damage, int repeatDelay);

private:
    Timer* m_Timer = nullptr;
};

