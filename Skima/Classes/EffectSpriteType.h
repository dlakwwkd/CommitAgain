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
	void			CreateSprite(const char* file, const Vec2& createPos, float scale, float lastTime);
	void			AddSubSprite(const char* file, const Vec2& anchorPoint, const Vec2& createPos, float scale);
	Animate*        MakeAnimationOnce(const char* format, int size);
    Animate*        MakeExplodeAnimation(const char* format, int size);
	void			ExtinctSprite();

protected:
	Sprite*         m_Sprite = nullptr;
};

