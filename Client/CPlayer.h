#pragma once
#include "CObject.h"

class CTexture;

class CPlayer :
    public CObject
{
private:

public:
    virtual void update();
    virtual void render(HDC _hdc);

public: 
    CPlayer();
    ~CPlayer();

};

