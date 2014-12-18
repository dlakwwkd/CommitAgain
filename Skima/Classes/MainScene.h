#pragma once

USING_NS_CC;

class MainScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);

    void menuCallback1(Ref* sender);
    void menuCallback2(Ref* sender);
    void menuCallback3(Ref* sender);
};

