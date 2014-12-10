#pragma once
enum BodyShape
{
    CIRCLE,
    BOX,
};

enum GameMode
{
    SINGLE,
    MULTI,
};

enum CursorMode
{
    CURSOR_DEFAULT,
    CURSOR_ATTACK,
    CURSOR_TELEPORT,
    CURSOR_SPLASH,
};

enum Direction
{
    E,
    W,
    S,
    N,
    SE,
    SW,
    NE,
    NW
};

enum GameResult
{
    WIN,
    LOSE,
};