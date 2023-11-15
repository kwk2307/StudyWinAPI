#pragma once
#include "CUI.h"
class CPanel :
    public CUI
{
private:
    Vec2 m_vPreMousePos;

public:
    virtual void OnMouseTap();
    virtual void OnMouseAway();
    virtual void OnMouseHold();

};

