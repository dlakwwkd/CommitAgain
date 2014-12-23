#include "stdafx.h"
#include "Map.h"
#include "Scheduler.h"
#include "GameManager.h"
#include "ClientSession.h"
#include "MoveRock.h"
#include "Player.h"
#include "Lava.h"

Map::Map(int roomId)
{
    b2Vec2 edgePos = { MAX_MAP_SIZE_X, MAX_MAP_SIZE_Y};
    edgePos = CONVERT_IN(edgePos, roomId);

    b2Vec2 startPos = { edgePos.x - Reduce(MAX_MAP_SIZE_X), edgePos.y - Reduce(MAX_MAP_SIZE_Y) };

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

void Map::InitMap(Player* player, int roomId)
{
    for (int i = 0; i < 5; ++i)
    {
        auto pos = b2Vec2(static_cast<float>(rand() % MAX_MAP_SIZE_X), static_cast<float>(rand() % MAX_MAP_SIZE_Y));
        auto rock = new MoveRock(player, b2Vec2(CONVERT_IN(pos, roomId)));
        player->GetClient()->SendMapInfo(player->GetPlayerID(), rock->GetUnitID(), rock->GetBody()->GetPosition());
    }
}

void Map::LavaCreate(Player* player, int roomId)
{
    if (player->GetClient()->GetPlayer() == nullptr)
    {
        return;
    }
    auto pos = b2Vec2(static_cast<float>(rand() % MAX_MAP_SIZE_X), static_cast<float>(rand() % MAX_MAP_SIZE_Y));
    auto lava = new Lava(player, b2Vec2(CONVERT_IN(pos, roomId)));         
    player->GetClient()->SendMapInfo(player->GetPlayerID(), lava->GetUnitID(), lava->GetPos());
}
