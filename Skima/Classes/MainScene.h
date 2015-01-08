#pragma once
class InputBox;

USING_NS_CC;

class MainScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);

    void menuCallback1(Ref* sender);
    void menuCallback2(Ref* sender);

    void LoginToServer();

private:
    void ConnectLabelCreate(const char* str, MainScene* scene);
    void ConnectLabelChange(const char* str);
    void InitBackground();
    void InitSound();

private:
    std::string m_LoginName;
    InputBox*   m_LoginBox = nullptr;
};

