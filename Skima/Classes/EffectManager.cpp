#include "pch.h"
#include "EffectManager.h"
#include "FireEffect.h"
#include "IceEffect.h"

EffectManager::EffectManager()
{
	m_EffectList.reserve(EffectPoolSize::E_TOTAL);

	int i, ID;

	for (i = 0; i < EffectPoolSize::FIRE; ++i)
	{
		ID = EffectIDBoundary::FIRE_ID_START + i;
		m_EffectList.push_back(new FireEffect(ID));
	}
	m_LastID_FireEffect = ID;

	for (i = 0; i < EffectPoolSize::ICE; ++i)
	{
		ID = EffectIDBoundary::ICE_ID_START + i;
		m_EffectList.push_back(new IceEffect(ID));
	}
	m_LastID_IceEffect = ID;
}


EffectManager::~EffectManager()
{
	for (auto& effect : m_EffectList)
	{
		delete effect;
	}
}

Effect* EffectManager::Assign(EffectType type)
{
	for (auto& effect : m_EffectList)
	{
		if (effect->m_EffectType == type && !effect->m_InUse)
		{
			effect->m_InUse = true;
			return effect;
		}
	}

	if (!Expand(type))
	{
		return nullptr;
	}
	return m_EffectList.back();
}

void EffectManager::Release(Effect* effect)
{
	effect->m_InUse = false;
}

bool EffectManager::Expand(EffectType type)
{
	int i, ID;

	switch (type)
	{
	case EF_NONE:
		return false;
		break;
	case EF_FIRE:
		for (i = 1; i < EffectPoolSize::FIRE; ++i)
		{
			ID = m_LastID_FireEffect + i;
			m_EffectList.push_back(new FireEffect(ID));
		}
		m_LastID_FireEffect = ID;
		break;
	case EF_ICE:
		for (i = 1; i < EffectPoolSize::ICE; ++i)
		{
			ID = m_LastID_IceEffect + i;
			m_EffectList.push_back(new IceEffect(ID));
		}
		m_LastID_IceEffect = ID;
		break;
	}
	return true;
}
