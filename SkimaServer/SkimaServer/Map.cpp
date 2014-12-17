﻿#include "stdafx.h"
#include "Map.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "ClientSession.h"
#include "MoveRock.h"
#include "Player.h"


Map::Map(int roomId)
{
    b2Vec2 edgePos = { MAX_MAP_SIZE_X, MAX_MAP_SIZE_Y};
    edgePos = CONVERT_IN(edgePos, roomId);

    b2Vec2 startPos = { edgePos.x - REDUCE(MAX_MAP_SIZE_X), edgePos.y - REDUCE(MAX_MAP_SIZE_Y) };

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    m_Body = GGameManager->GetWolrd()->CreateBody(&groundBodyDef);

    b2EdgeShape groundEdge;
    b2FixtureDef boxShapeDef;
    boxShapeDef.shape = &groundEdge;

    auto createLine = [&](const b2Vec2& v1, const b2Vec2& v2)
    {
        groundEdge.Set(v1, v2);
        m_Body->CreateFixture(&boxShapeDef);
    };
    createLine(b2Vec2(startPos.x, edgePos.y), edgePos); //상
    createLine(startPos, b2Vec2(edgePos.x, startPos.y));//하
    createLine(startPos, b2Vec2(startPos.x, edgePos.y));//좌
    createLine(b2Vec2(edgePos.x, startPos.y), edgePos); //우

    m_Body->SetUserData(nullptr);

    m_MapObjectList.reserve(MAX_OBSTRUCT_SIZE);
}


Map::~Map()
{
    CallFuncAfter(1, GGameManager, &GameManager::DeleteBody, m_Body);
}

void Map::InitMap(int roomId, Player* player)
{
    for (int i = 0; i < 5; ++i)
    {
        auto pos = b2Vec2(rand() % MAX_MAP_SIZE_X, rand() % MAX_MAP_SIZE_Y);
        MoveRock* rock = new MoveRock(player, b2Vec2(CONVERT_IN(pos, roomId)));

        m_MapObjectList.push_back(rock);
        player->GetClient()->SendMapInfo(rock->GetUnitID(), rock->GetBody()->GetPosition());
    }
}

void Map::ObjectListClear()
{
    for (auto& mapObject : m_MapObjectList)
    {
        delete mapObject;
        mapObject = nullptr;
    }
    m_MapObjectList.clear();
}
