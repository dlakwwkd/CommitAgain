#include "pch.h"
#include "EffectManager.h"
#include "FireEffect.h"
#include "IceEffect.h"
#include "TeleportEffect.h"
#include "LightningEffect.h"
#include "SparkEffect.h"

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

    for (i = 0; i < EffectPoolSize::TELE; ++i)
    {
        ID = EffectIDBoundary::TELE_ID_START + i;
        m_EffectList.push_back(new TeleportEffect(ID));
    }
    m_LastID_TeleEffect = ID;

    for (i = 0; i < EffectPoolSize::LIGHTNING; ++i)
    {
        ID = EffectIDBoundary::LIGHTNING_ID_START + i;
        m_EffectList.push_back(new LightningEffect(ID));
    }
    m_LastID_LightningEffect = ID;

    for (i = 0; i < EffectPoolSize::SPARK; ++i)
    {
        ID = EffectIDBoundary::SPARK_ID_START + i;
        m_EffectList.push_back(new SparkEffect(ID));
    }
    m_LastID_SparkEffect = ID;
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
    case EF_SPARK:
        for (i = 1; i < EffectPoolSize::SPARK; ++i)
        {
            ID = m_LastID_SparkEffect + i;
            m_EffectList.push_back(new IceEffect(ID));
        }
        m_LastID_SparkEffect = ID;
        break;
    case EF_TELE:
        for (i = 1; i < EffectPoolSize::TELE; ++i)
        {
            ID = m_LastID_TeleEffect + i;
            m_EffectList.push_back(new TeleportEffect(ID));
        }
        m_LastID_TeleEffect = ID;
        break;
    case EF_LIGHTNING:
        for (i = 1; i < EffectPoolSize::LIGHTNING; ++i)
        {
            ID = m_LastID_LightningEffect + i;
            m_EffectList.push_back(new LightningEffect(ID));
        }
        m_LastID_LightningEffect = ID;
        break;
    }
    return true;
}
