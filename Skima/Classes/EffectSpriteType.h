#pragma once
#include "Effect.h"
class EffectSpriteType : public Effect
{
public:
	EffectSpriteType();
	virtual ~EffectSpriteType();

	virtual void	CreateEffect(const Vec2& createPos) = 0;
	virtual void	ExtinctEffect()						= 0;

protected:
    Animate*        MakeAnimation(const char* format, int size, float delay);
    void			CreateSprite(const char* file, const Vec2& createPos, float scale, float lastTime);
	void			AddSubSprite(const char* file, const Vec2& anchorPoint, const Vec2& createPos, float scale);
	void			ExtinctSprite();

protected:
	Sprite*         m_Sprite = nullptr;
};

