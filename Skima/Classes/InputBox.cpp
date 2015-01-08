#include "pch.h"
#include "InputBox.h"
#include "MainScene.h"
#pragma comment (lib, "imm32")

USING_NS_CC;

InputBox *InputBox::create(const std::string &str, const std::string &name, float size)
{
    auto i = new InputBox();

    if (i && i->init(str, name, size))
    {
        i->autorelease();
        return i;
    }
    CC_SAFE_DELETE(i);
    return nullptr;
}

void InputBox::beginInput()
{
    SetFocus(m_Editbox);
    restoreConvMode();
}
void InputBox::endInput()
{
    HWND hWnd = Director::getInstance()->getOpenGLView()->getWin32Window();

    saveConvMode();
    SetFocus(hWnd);

    /* */
    HIMC ime = ImmGetContext(hWnd);
    ImmSetConversionStatus(ime, IME_CMODE_NOCONVERSION, 0);
    ImmReleaseContext(hWnd, ime);
}

void InputBox::clear()
{
    setString("");
    SetWindowText(m_Editbox, L"");
}


bool InputBox::init(const std::string &str, const std::string &name, float size)
{
    if (!LabelTTF::initWithString(str, name, size))
        return false;

    HWND hWnd = Director::getInstance()->getOpenGLView()->getWin32Window();
    m_Editbox = CreateWindowA("edit", "", WS_CHILD | WS_VISIBLE, -1000, 0, 1000, 40, hWnd, 0, GetModuleHandle(0), NULL);

    SendMessage(m_Editbox, EM_SETLIMITTEXT, (WPARAM)size, NULL);
    SendMessage(m_Editbox, EM_SETIMESTATUS, (WPARAM)EMSIS_COMPOSITIONSTRING, (LPARAM)EIMES_CANCELCOMPSTRINFOCUS);

    SetWindowLongPtr(m_Editbox, GWLP_USERDATA, (long)this);
    m_OldProc = (WNDPROC)SetWindowLongPtr(m_Editbox, GWLP_WNDPROC, (long)HookProc);

    return true;
}

LRESULT InputBox::HookProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    auto _this = (InputBox*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    auto result = CallWindowProc(_this->m_OldProc, hWnd, Msg, wParam, lParam);
    auto mainScene = (MainScene*)_this->getParent()->getParent()->getParent();
    switch (Msg)
    {
    case WM_KEYDOWN:
        if (wParam == VK_RETURN)
        {   
            mainScene->LoginToServer();
        }
        break;
    case WM_IME_COMPOSITION:
    case WM_IME_NOTIFY:
        _this->refreshContent();
        break;
    }
    return result;
}

void InputBox::refreshContent()
{
    wchar_t *msg = new wchar_t[m_MaxLength];
    char *cmsg = new char[m_MaxLength * 3];

    GetWindowText(m_Editbox, msg, m_MaxLength);
    WideCharToMultiByte(CP_ACP, 0, msg, -1, cmsg, m_MaxLength * 3, 0, 0);

    setString(cmsg);

    delete[] msg;
    delete[] cmsg;
}

void InputBox::saveConvMode()
{
    HIMC ime = ImmGetContext(m_Editbox);
    ImmGetConversionStatus(ime, &m_LastConv, nullptr);
    ImmReleaseContext(m_Editbox, ime);
}
void InputBox::restoreConvMode()
{
    HIMC ime = ImmGetContext(m_Editbox);
    ImmSetConversionStatus(ime, m_LastConv, 0);
    ImmReleaseContext(m_Editbox, ime);
}
