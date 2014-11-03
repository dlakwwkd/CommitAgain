#pragma once
#include "cocos2d.h"

class NetworkGameScene : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
	virtual bool init();  
    CREATE_FUNC(NetworkGameScene);

	bool IsStartGame(){ return m_IsStartGame; }

	void StartGame();
	void RemoveLoadingLayer();

private:
	bool m_IsStartGame;
};
