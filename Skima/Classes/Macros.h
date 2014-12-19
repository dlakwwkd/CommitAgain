#pragma once
///////////////////////////////////////////////////////////////////////////
/*
    씬을 불러오기위한 매크로
*/
///////////////////////////////////////////////////////////////////////////
#define GET_NETWORK_SCENE   dynamic_cast<NetworkScene*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("NetworkScene"))
#define GET_ROOM_SCENE      dynamic_cast<RoomScene*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("RoomScene"))
#define GET_GAME_SCENE		dynamic_cast<GameScene*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene"))
#define GET_LOADING_LAYER   dynamic_cast<LoadingBGLayer*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->getChildByName("LoadingBGLayer"))
#define GET_OBJECT_LAYER    dynamic_cast<ObjectLayer*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->getChildByName("ListenerLayer")->getChildByName("ObjectLayer"))
#define GET_MAP_LAYER       dynamic_cast<MapLayer*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->getChildByName("ListenerLayer")->getChildByName("MapLayer"))
#define GET_UI_LAYER        dynamic_cast<UILayer*>(cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameScene")->getChildByName("UILayer"))


///////////////////////////////////////////////////////////////////////////
/*
    좌표타입 변환을 위한 매크로
*/
///////////////////////////////////////////////////////////////////////////
#define DISPLAY_X 1280
#define DISPLAY_Y 800
#define MAX_MAP_SIZE_X 1680
#define MAX_MAP_SIZE_Y 1050

#define CONVERT(v) {(v).x, (v).y}

///////////////////////////////////////////////////////////////////////////
/*
    UnitID에서 타입 체크를 하기 위한 매크로
*/
///////////////////////////////////////////////////////////////////////////
#define MAIN_TYPE_BIT   0xF0000000
#define MAIN_TYPE_BIT_T 0x0FFFFFFF
#define SIDE_TYPE_BIT   0x0F000000
#define SIDE_TYPE_BIT_T 0xF0FFFFFF

#define SET_MAIN_TYPE(unitID, type) (((unitID) & MAIN_TYPE_BIT_T) + ((type) << 28))
#define SET_SIDE_TYPE(unitID, type) (((unitID) & SIDE_TYPE_BIT_T) + (((type) << 24) & MAIN_TYPE_BIT_T))
#define INIT_MAIN_TYPE(unitID)      ((unitID) & MAIN_TYPE_BIT_T)
#define INIT_SIDE_TYPE(unitID)      ((unitID) & SIDE_TYPE_BIT_T)
#define GET_MAIN_TYPE(unitID)       (((unitID) & MAIN_TYPE_BIT) >> 28)
#define GET_SIDE_TYPE(unitID)       (((unitID) & SIDE_TYPE_BIT) >> 24)
