#pragma once

USING_NS_CC;

class EscLayer : public LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(EscLayer);

    void SetLoadingFin(){ m_IsLoadingFin = true; }
    bool IsLoadingFin(){ return m_IsLoadingFin; }
    
    void Tick(float dt);

private:
    bool m_IsLoadingFin;
};

