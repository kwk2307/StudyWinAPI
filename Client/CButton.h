#pragma once
#include "CUI.h"
class CButton :
    public CUI
{
    enum BtnState
    {
        None,
        Hover,
        Clicked,
        Disable
    };

private:
    BtnState m_eState;

public:
    virtual void update();
public:
    void OnButtonClick();
public:
    CButton();
    ~CButton();
};

