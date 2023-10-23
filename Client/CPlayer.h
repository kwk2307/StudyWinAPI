#pragma once
#include "CObject.h"
class CPlayer :
    public CObject
{
    void update();
    void render(HDC _hdc);
};

