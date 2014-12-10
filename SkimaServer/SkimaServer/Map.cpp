#include "stdafx.h"
#include "Map.h"
#include "Scheduler.h"
#include "GameManager.h"


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
}


Map::~Map()
{
    CallFuncAfter(1, GGameManager, &GameManager::DeleteBody, m_Body);
}
