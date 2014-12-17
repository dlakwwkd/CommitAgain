#include "pch.h"
#include "SparkEffect.h"


SparkEffect::SparkEffect()
{
}


SparkEffect::~SparkEffect()
{
}

void SparkEffect::CreateEffect(const Vec2& createPos)
{
	CreateParticle("Jupiter/spark_effect.plist", createPos, 0.5f, 2.0f);
}

void SparkEffect::ExtinctEffect()
{
	ExtinctParticle();
}
