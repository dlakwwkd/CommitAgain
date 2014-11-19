#pragma once

USING_NS_CC;

class MultiGameScene : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
	virtual bool init();  
    CREATE_FUNC(MultiGameScene);

	bool IsStartGame(){ return m_IsStartGame; }

	void StartGame();
	void RemoveLoadingLayer();

private:
	bool m_IsStartGame;
};
