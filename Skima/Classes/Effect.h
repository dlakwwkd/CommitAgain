#pragma once
#include "EffectManager.h"

USING_NS_CC;

class Effect
{
public:
	Effect();
	virtual ~Effect();

	virtual void CreateEffect(Vec2 createPos) = 0;
	virtual void ExtinctEffect() = 0;

protected:
	EffectType		m_EffectType;
	Sprite*			m_Sprite;
	bool			m_InUse;
	int				m_ID;

	friend class EffectManager;
};

