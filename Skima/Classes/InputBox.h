#pragma once
class MainScene;

class InputBox : public cocos2d::LabelTTF
{
public:
    static InputBox* create(const std::string& str, const std::string& name, float size);

    void beginInput();
    void endInput();

    void clear();

protected:
    InputBox() : m_MaxLength(255), m_Editbox(nullptr), m_LastConv(IME_CMODE_NATIVE){}
    virtual ~InputBox(){}

    virtual bool init(const std::string& str, const std::string& name, float size);

    static LRESULT HookProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

    void refreshContent();

    void saveConvMode();
    void restoreConvMode();

private:
    int         m_MaxLength;
    bool        m_InputEnabled;
    HWND        m_Editbox;
    WNDPROC     m_OldProc;
    DWORD       m_LastConv;
};

