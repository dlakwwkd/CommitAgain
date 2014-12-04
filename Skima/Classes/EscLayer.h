#pragma once

USING_NS_CC;

class EscLayer : public LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(EscLayer);

    void menuCallback1(Ref* sender);
    void menuCallback2(Ref* sender);

    void ShowEscLayer();
};

