#pragma once
//////////////////////////////////////////////////////////////////////////
/*
    addChild 태그
*/
//////////////////////////////////////////////////////////////////////////
/// Scene
#define MAIN_SCENE          "MainScene"
#define NETWORK_SCENE       "NetworkScene"
#define ROOM_SCENE          "RoomScene"
#define GAME_SCENE          "GameScene"
#define GAMEOVER_SCENE      "GameOverScene"

/// Layer
#define MAKEROOM_LAYER      "MakeRoomLayer"
#define WAITING_LAYER       "WaitingLayer"
#define LISTENER_LAYER      "ListenerLayer"
#define OBJECT_LAYER        "ObjectLayer"
#define LOADING_LAYER       "LoadingBGLayer"
#define UI_LAYER            "UILayer"
#define ESC_LAYER           "EscLayer"
#define MAP_LAYER           "MapLayer"

/// Label
#define CONNECT_LABEL       "ConnectLabel"
#define MAX_PLAYER_LABEL    "MaxPlayerNumLabel"
#define ROOM_STATE_LABEL    "RoomStateLabel"
#define TEAM_STATE_LABEL    "TeamStateLabel"
#define PLAYER_NUM_LABEL    "PlayerNumLabel"
#define GAMEOVER_MANU_LABEL "GameOverMenu"
#define HP_LABEL            "HpLabel"

/// Sprite
#define ROOM_LIST_FRAME     "RoomListFrame"
#define MELEE_SELECT        "MeleeSelect"
#define TEAM_SELECT         "TeamSelect"
#define HP_BAR              "Hpbar"



//////////////////////////////////////////////////////////////////////////
/*
    Label 내용
*/
//////////////////////////////////////////////////////////////////////////
#define DEF_FONT                "Thonburi"

#define LOGIN_BOX_INIT_TEXT     "이름을 입력"
#define TRY_CONNECT_TEXT        "로그인 시도 중......"
#define CONNECT_FAILED_TEXT     "로그인 실패."
#define CONNECT_SUCCESS_TEXT    "로그인 성공!!"
#define CONNECT_GOOD_TEXT       "서버 연결 양호."
#define JOIN_ROOM_REQUEST_TEXT  "방 참여 혹은 방 생성을 해주십시오."
#define TRY_JOIN_ROOM_TEXT      "방에 들어가는 중..."
#define ROOM_IS_STARTED_TEXT    "이미 게임이 시작된 방입니다."
#define ROOM_IS_FULL_TEXT       "방의 인원이 초과하였습니다."
#define ROOM_INFO_WAITING_TEXT  "연결 중..."

#define ROOM_NUM_TEXT           "번 방"
#define PLAYER_NUM_TEXT         "방 인원: "
#define CUR_PLAYER_NUM_TEXT     "명 / "
#define MAX_PLAYER_NUM_TEXT     "명"
#define TEAM_1_TEXT             "1 팀"
#define TEAM_2_TEXT             "2 팀"

#define LOADING_TEXT            "Loading..."
#define WAITING_TEXT            "다른 플레이어 기다리는 중..."
#define GAME_START_TEXT         "게임을 시작합니다."


#define EXIT_TEXT               "Exit"
#define CONTINUE_TEXT           "계속하기"
#define GAME_OUT_TEXT           "나가기"


