#pragma once

#define DISPLAY_X 1280
#define DISPLAY_Y 800

USING_NS_CC;

class MainScene : public LayerColor
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);

    void menuCallback1(Ref* sender);
    void menuCallback2(Ref* sender);
    void menuCallback3(Ref* sender);
};

