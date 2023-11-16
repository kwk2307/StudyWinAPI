#pragma once
#include "CUI.h"
class CButton :
    public CUI
{
private:

    // 함수 포인터를 통해 버튼 이벤트 구현 
    
public:
    virtual void update();

public:
    void OnButtonClick();

public:
    CButton();
    ~CButton();
};

