#pragma once

USING_NS_CC;

class MultiGameScene : public Layer
{
public:
    
    static Scene* createScene();
	virtual bool init();  
    CREATE_FUNC(MultiGameScene);

	bool IsStartGame(){ return m_IsStartGame; }

	void StartGame();
	void RemoveLoadingLayer();

private:
	bool m_IsStartGame;
};
