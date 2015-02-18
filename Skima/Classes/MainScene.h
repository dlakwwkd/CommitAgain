#pragma once

USING_NS_CC;

class InputBox;
class MainScene : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);

    void menuCallback1(Ref* sender);
    void menuCallback2(Ref* sender);
    void servIpCallback(Ref* sender);

    void ConnectLabelCreate(const char* str, MainScene* scene);
    void ConnectLabelChange(const char* str);
    void LoginToServer();
    void InputServerIp();

private:
    std::string m_LoginName;
    InputBox*   m_LoginBox;
    std::string m_ServIP;
    InputBox*   m_ServIPBox;

};

