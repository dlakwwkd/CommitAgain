#pragma once

USING_NS_CC;

class Effect
{
public:
    Effect();
    virtual ~Effect();

    virtual void	CreateEffect(const Vec2& createPos) = 0;
    virtual void	ExtinctEffect()						= 0;
};

