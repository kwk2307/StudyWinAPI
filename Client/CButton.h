#pragma once
#include "CUI.h"
class CButton :
    public CUI
{
private:

    // �Լ� �����͸� ���� ��ư �̺�Ʈ ���� 
    
public:
    virtual void update();

public:
    void OnButtonClick();

public:
    CButton();
    ~CButton();
};

