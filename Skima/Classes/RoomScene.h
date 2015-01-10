#pragma once
#include "PacketType.h"

USING_NS_CC;

typedef std::map<HeroType, Sprite*> FaceList;


class RoomScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(RoomScene);

    void ClickHero(HeroType heroType);
    void Tick(float dt);

    void SetRoomID(int id) { m_RoomInfo.mRoomNum = id; };
    void UpdateRoomInfo(const RoomInfo& roomInfo);
    void PrintMenuByRoomType();

    void TeamSelectACallback(Ref* sender);
    void TeamSelectBCallback(Ref* sender);
    void GameStartCallback(Ref* sender);
    void GameExitCallback(Ref* sender);

    void GameStart();
    void GameStartComplete();

private:
    void WaitingCheck();
    void MakeHeroSprite(const char* image, Vec2 pos, Vec2 scale, Vec2 anchor, HeroType hero);
    void SetFaceProperty(MenuItemImage* img, Vec2 pos, Vec2 scale, Vec2 anchor);
    void ChangeSelectedHero(HeroType heroType);

private:
    RoomInfo    m_RoomInfo;
    bool        m_IsReady;
    HeroType    m_CurHero;
    Team        m_CurTeam;
    FaceList    m_HeroImageList;
};
