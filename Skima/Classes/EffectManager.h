#pragma once
#include "..\..\PacketType.h"
class Effect;

enum EffectType
{
	EF_NONE,

	EF_FIRE,
	EF_ICE,
};

enum EffectPoolSize
{
	E_TOTAL	= 1000,
	FIRE	= 200,
	ICE		= 200,
};

enum EffectIDBoundary
{
	E_ID_INTERVAL	= 1000,
	EFFECT_ID_START	= 20001,
	FIRE_ID_START	= EFFECT_ID_START + E_ID_INTERVAL,
	ICE_ID_START	= FIRE_ID_START + E_ID_INTERVAL,
};

class EffectManager
{
public:
	EffectManager();
	virtual ~EffectManager();

	Effect*		Assign(EffectType type);
	void		Release(Effect* effect);
private:
	bool		Expand(EffectType type);

private:
	std::vector<Effect*>	m_EffectList;

	int						m_LastID_FireEffect;
	int						m_LastID_IceEffect;
};

