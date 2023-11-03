#pragma once
#include "CObject.h"
class CBlock :
    public CObject
{
public:
    virtual void update();

public:
    virtual void OnCollision(CCollider* _pOther);


public:
    CBlock();
    ~CBlock();
};

