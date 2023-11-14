#pragma once
#include "CUI.h"
class CButton :
    public CUI
{
private:

public:
    virtual void update();

public:
    void OnButtonClick();

public:
    CButton();
    ~CButton();
};

