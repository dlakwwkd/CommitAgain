#pragma once
#include "cocos2d.h"

USING_NS_CC;

class LoadingBGLayer : public LayerColor
{
public:
	virtual bool init();
	CREATE_FUNC(LoadingBGLayer);

	void SetLoadingFin(){ m_IsLoadingFin = true; }
	bool IsLoadingFin(){ return m_IsLoadingFin; }
	
	void Tick(float dt);

private:
	bool m_IsLoadingFin;
};

