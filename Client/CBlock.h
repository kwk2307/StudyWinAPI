#pragma once
#include "CObject.h"
class CBlock :
    public CObject
{
public:
    virtual void update();
public:
    CBlock();
    ~CBlock();
};

