﻿#pragma once
#include "PacketType.h"

USING_NS_CC;

typedef std::map<HeroType, Sprite*> FaceList;


class RoomScene : public LayerColor
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(RoomScene);

    void SetRoomID(int id) { m_RoomID = id; };
    void GameStartCallback(Ref* sender);
    void GameExitCallback(Ref* sender);
    void WaitingCheck();

    void MakeFaceSprite(const char* image, Vec2 pos, Vec2 scale, Vec2 anchor, HeroType hero);
	void SetFaceProperty(MenuItemImage* img, Vec2 pos, Vec2 scale, Vec2 anchor);
	void ChangeSelectedHero();

    void Tick(float dt);
	void ClickMagician();
	void ClickJupiter();

    void GameStartComplete();

private:
    int         m_RoomID;
    bool        m_IsReady;
	HeroType    m_CurHero;
	FaceList    m_Facelist;
    LayerColor* m_WaitingLayer;

};
