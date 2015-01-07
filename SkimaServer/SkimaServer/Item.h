#pragma once
#include "Unit.h"
#include "ObjectPool.h"
#include "GameManager.h"
class Mob;
class Timer;

class Item : public Unit, public ObjectPool<Item>
{
public:
    Item(Mob* mob, BuffTarget buffType);
    virtual ~Item();

    BuffTarget      GetBuffTarget() { return m_BuffType; }
    Rect*           GetTakeRange(){ return &m_TakeRange; }

    virtual void    Dead();

private:
    ItemType    m_Type;
    BuffTarget  m_BuffType;
    Rect        m_TakeRange;
    Timer*      m_Timer = nullptr;
};

