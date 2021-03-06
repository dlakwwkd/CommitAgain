#pragma once
#include "..\..\PacketType.h"
class Effect;

enum EffectType
{
    EF_NONE,

	EF_FIRE,
	EF_ICE,
    EF_SPARK,
    EF_LIGHTNING,
    EF_TELE,
};

enum EffectPoolSize
{
    E_TOTAL = 250,
    FIRE = 50,
    ICE = 50,
    SPARK = 50,
    TELE = 50,
    LIGHTNING = 50,
};

enum EffectIDBoundary
{
    E_ID_INTERVAL = 200,
    EFFECT_ID_START = 2001,
    FIRE_ID_START = EFFECT_ID_START + E_ID_INTERVAL,
    ICE_ID_START = FIRE_ID_START + E_ID_INTERVAL,
    TELE_ID_START = ICE_ID_START + E_ID_INTERVAL,
    LIGHTNING_ID_START = TELE_ID_START + E_ID_INTERVAL,
    SPARK_ID_START = LIGHTNING_ID_START + E_ID_INTERVAL,
};

class EffectManager
{
public:
    EffectManager();
    ~EffectManager();

    Effect* Assign(EffectType type);
    void    Release(Effect* effect);
private:
    bool    Expand(EffectType type);

private:
    std::vector<Effect*>    m_EffectList;
    int                     m_LastID_FireEffect;
    int                     m_LastID_IceEffect;
    int                     m_LastID_SparkEffect;
    int                     m_LastID_TeleEffect;
    int                     m_LastID_LightningEffect;
};

