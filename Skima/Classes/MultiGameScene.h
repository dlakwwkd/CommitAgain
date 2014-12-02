#pragma once
#include "Enums.h"

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
    void GameOver(int playerId, int loseId);

private:
    bool m_IsStartGame;
};
