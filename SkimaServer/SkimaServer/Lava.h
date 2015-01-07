#pragma once
#include "MapObject.h"
#include "ObjectPool.h"
#include "GameManager.h"
class LavaDamageSkill;

class Lava : public MapObject, public ObjectPool<Lava>
{
public:
    Lava(Player* owner, b2Vec2 createPos);
    virtual ~Lava();

    Rect* GetRange(){ return &m_Range; }

private:
    Rect            m_Range;
    LavaDamageSkill*    m_Damage;
};

